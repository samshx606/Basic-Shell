# Simple Shell Program

This is a simple shell program written in C. It allows users to execute commands interactively or in batch mode. The shell supports basic built-in commands such as `exit` and `cd`, and searches for executable commands in directories listed in the system's `PATH` environment variable.

## Features

- **Interactive Mode**: Prompts the user to enter commands one at a time.
- **Batch Mode**: Executes commands from a file without user interaction.
- **Built-in Commands**: Supports `exit` to terminate the shell and `cd` to change directories.
- **Command Execution**: Searches the directories listed in `PATH` and executes commands in a new child process.

## Compilation

To compile the program, use the following command:

```bash
gcc -o wish shell.c
```
## Usage

### Interactive Mode

To run the shell interactively, simply execute:

```bash
./wish
```

Once running, the shell will display the prompt:

```bash
wish>
```

You can then enter commands directly. Here are some examples of what you can do in interactive mode:

- **Change the directory with `cd`**:

  ```bash
  wish> cd /home/user
  ```

- **List files in the current directory**:

  ```bash
  wish> ls
  ```

- **Exit the shell**:

  ```bash
  wish> exit
  ```

The shell will continue running until you type `exit` or close the terminal.

### Batch Mode

To run the shell in batch mode, provide a filename containing a list of commands as an argument:

```bash
./wish batchfile.txt
```





Where `batchfile.txt` is a text file containing a series of commands to be executed. The shell will process the commands in the file sequentially.

Example `batchfile.txt`:

```bash
cd /home/user
ls
exit
```

In batch mode, the shell will not display the `wish>` prompt. It will execute the commands in the file and then exit once the `exit` command is reached or all commands are executed.

### Built-in Commands

The following built-in commands are supported:

- **`exit`**: Exits the shell. The shell will print `Exiting shell` before terminating.
- **`cd <directory>`**: Changes the current working directory to `<directory>`. If the `chdir` function fails (e.g., the directory doesn't exist), an error message will be displayed.

### Command Execution

For commands other than built-in commands, the shell will:

1. **Parse the command**: The command entered by the user is split into arguments.
2. **Fork a child process**: The shell creates a new process to execute the command.
3. **Search the `PATH`**: The shell checks each directory in the `PATH` environment variable to find the executable for the command.
4. **Execute the command**: If the command is found, it is executed. If not, the shell will display an error message.

Example:

```bash
wish> ls
```

If the `ls` command is in one of the directories listed in `PATH`, it will be executed. If not, the shell will display an error message.

## Error Handling

The shell includes basic error handling:

- **No `PATH` environment variable**: If the `PATH` environment variable is not set, an error message will be displayed.
- **Command not found**: If a command is not found in the directories listed in `PATH`, the shell will print an error message.
- **Failed `cd` command**: If the `cd` command fails (e.g., the directory does not exist), an error message will be displayed.
- **Forking error**: If the shell fails to create a child process (forking error), it will print an error message.

## Example Usage

### Example 1: Interactive Mode

```bash
$ ./wish
wish> cd /home/user
wish> ls
wish> exit
Exiting shell
```

### Example 2: Batch Mode

Given a `batchfile.txt` containing:

```bash
cd /home/user
ls
exit
```

Run the shell in batch mode:

```bash
$ ./wish batchfile.txt
```

The shell will execute the commands from `batchfile.txt` in sequence and exit after completing them.

## Limitations

- **No command history**: The shell does not store or support a history of executed commands.
- **No background processes**: The shell does not support running commands in the background using `&`.
- **No signal handling**: The shell does not handle signals like `Ctrl+C` or `Ctrl+Z` for interrupting or backgrounding processes.
- **Limited built-in commands**: Only `exit` and `cd` are implemented as built-in commands.
- **No piping or redirection**: The shell does not support piping (`|`) or redirection (`>`, `<`) of input/output.
- **No tab completion**: The shell does not support auto-completion of commands or file paths.
## Resources

### Books
- **[Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/)**
  - A great resource for understanding operating system concepts.

