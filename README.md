# Simple Shell Implementation

## Overview

This project implements a simple shell program in C. The shell can execute commands, handle built-in commands like `cd` and `exit`, and supports batch mode for executing commands from a file. The shell parses the environment's PATH variable to locate executable files.

## Features

- Execute external commands.
- Built-in command support:
    - `cd <directory>`: Change the current directory.
    - `exit`: Exit the shell.
- Batch mode for executing commands from a file.
- Error handling for various situations.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc`).
- Basic knowledge of using the command line.

### Compilation

To compile the shell program, navigate to the project directory and run:

```bash
gcc -o simple_shell simple_shell.c
```

## Usage

You can run the shell in two modes:

### Interactive Mode:

```bash
./simple_shell
```

### Batch Mode:

```bash
./simple_shell <batch_file>
```

Replace `<batch_file>` with the path to a file containing commands, one per line.
