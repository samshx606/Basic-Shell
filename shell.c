#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Constants
#define MAX_LINE 1024
#define MAX_ARGS_COUNT 32
#define MAX_ARG_LEN 32

void print_error() {
    const char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

int main(int argc, char const *argv[]) {
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        print_error();
        return 1;
    }
    char path[MAX_LINE];
    char *paths[MAX_ARGS_COUNT];
    
    // Initialize path with values from the environment variable PATH
    char *token = strtok(path_env, ":");
    int path_count = 0;
    while (token != NULL && path_count < MAX_ARGS_COUNT) {
        paths[path_count++] = token;
        token = strtok(NULL, ":");
    }
    paths[path_count] = NULL; // Null-terminate the array

    // Check for batch mode
    FILE *batch_file = NULL;
    if (argc == 2) {
        batch_file = fopen(argv[1], "r");
        if (!batch_file) {
            print_error();
            return 1;
        }
    }

    while (1) {
        // Print prompt
        if (!batch_file) {
            printf("wish> ");
        }

        // Get command
        char command[MAX_LINE];
        if (batch_file) {
            if (fgets(command, sizeof(command), batch_file) == NULL) {
                exit(0);
            }
        } else {
            if (fgets(command, sizeof(command), stdin) == NULL) {
                printf("\nExiting shell\n");
                exit(0);
            }
        }
        command[strcspn(command, "\n")] = 0;

        // Handle built-in commands
        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell\n");
            exit(0);
        } else if (strncmp(command, "cd ", 3) == 0) {
            char *dir = command + 3;
            if (chdir(dir) != 0) {
                print_error();
            }
            continue;
        }

        // Parse command
        char *args[MAX_ARGS_COUNT];
        int i = 0;
        args[i] = strtok(command, " ");
        while (args[i] != NULL && i < MAX_ARGS_COUNT - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;
        if (args[0] == NULL)
            continue;

        // Execute command
        int pid = fork();
        if (pid < 0) {
            print_error();
            return 1;
        } else if (pid == 0) {  // Child process
            // Check command in paths
            int found = 0;
            for (int j = 0; j < path_count; j++) {
                snprintf(path, sizeof(path), "%s/%s", paths[j], args[0]);
                if (access(path, X_OK) == 0) {
                    execv(path, args);
                    print_error(); // execution failed
                    exit(1);
                }
            }
            print_error();  // Command not found
            exit(1);  // Exit child process if command is not found
        } else {  // Parent process
            wait(NULL);
        }
    }

    if (batch_file) {
        fclose(batch_file);
    }
    return 0;
}
