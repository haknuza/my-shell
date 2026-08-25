# Custom C Shell

A lightweight, custom command-line interpreter (shell) written in C. This project demonstrates core operating system concepts such as process creation, execution, and directory navigation using standard UNIX system calls.

## Features

- **Command Execution:** Parses and executes standard shell commands (e.g., `ls`, `pwd`, `echo`) using `fork()`, `execvp()`, and `waitpid()`.
- **Dynamic Argument Parsing:** Reads and tokenizes user input to handle commands with multiple arguments.
- **Built-in Commands:**
  - `cd [directory]`: Changes the current working directory. Defaults to the user's `HOME` directory if no argument is provided.
  - `exit`: Gracefully terminates the shell.
- **Dynamic Prompt:** Displays the current working directory directly in the command prompt.

## Prerequisites

To compile and run this shell, you need:
- A UNIX/Linux environment (or WSL on Windows).
- A C compiler, such as `gcc`.

## Installation & Compilation

1. Save the source code to a file, for example, `shell.c`.
2. Open your terminal and navigate to the directory containing the file.
3. Compile the code using `gcc`:

```bash
gcc -o myshell shell.c
```

## Usage

Run the compiled executable to start the custom shell:

```bash
./myshell
```

You will see a prompt displaying your current directory:

```bash
/home/user/current_dir --> 
```

From here, you can execute standard system commands:
```bash
/home/user/current_dir --> ls -la
/home/user/current_dir --> echo "Hello World"
/home/user/current_dir --> cd /tmp
/tmp --> pwd
```

To exit the shell, simply type:
```bash
/tmp --> exit
```

## Technical Details

- **Input Reading**: Uses `getline()` to dynamically read user input from standard input, managing memory allocation efficiently.
- **Tokenization**: The `GetArgsCount` and `FillInArgs` functions split the input string by spaces. They replace spaces with null terminators (`\0`) in-place, and store pointers to the beginning of each argument.
- **Execution Workflow**: 
  - The program checks for built-in commands (`cd`, `exit`) and handles them directly within the parent process to alter the shell's state.
  - For external commands, it calls `fork()` to spawn a child process. The child process replaces its memory image using `execvp()` to execute the requested command, while the parent process uses `waitpid()` to pause until the child completes.
