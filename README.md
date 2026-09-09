*This project has been created as part of the 42 curriculum by sabytheo and egache.*

# minishell

> *As beautiful as a shell*

## Description

**minishell** is a minimalistic reimplementation of a Unix shell, written in C and inspired by **bash**.

The goal of the project is to understand how a command interpreter works under the hood: how a raw line of text becomes a running process. Building it means dealing with process creation and synchronisation, file descriptor manipulation, environment handling, and signal management — all of it directly on top of the system calls, without any external help beyond `readline`.

The program displays a prompt, reads a command line, splits it into tokens, builds an execution structure, expands variables, and finally runs the resulting commands. It supports pipes, the four redirection types, quoting rules, environment variables, and the seven required builtins, and it reproduces bash's behaviour for interactive signals and exit codes.

In accordance with the subject, the program uses a **single global variable**, dedicated to receiving a signal number, and carrying no other information about the shell's state.

## Instructions

### Requirements

- `gcc` or `clang`
- `make`
- The **readline** library and its headers

```bash
# Debian / Ubuntu
sudo apt install libreadline-dev

# macOS (Homebrew)
brew install readline
```

### Compilation

```bash
git clone https://github.com/sabytheo/minishell.git
cd minishell
make
```

| Rule | Effect |
| --- | --- |
| `make` | Builds the `minishell` binary |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the binary |
| `make re` | Full rebuild |

### Execution

```bash
./minishell
```

The prompt waits for a command. `exit` or `Ctrl-D` leaves the shell.

Memory leaks can be checked with Valgrind. Since `readline()` allocates memory the program cannot free, a suppression file is used:

```bash
valgrind --leak-check=full --show-leak-kinds=all \
         --suppressions=readline.supp ./minishell
```

## Features

- **Interactive prompt** with a working command history
- **Executable lookup** through the `PATH`, or by relative / absolute path
- **Quoting**: single quotes `'` prevent any interpretation, double quotes `"` allow variable expansion
- **Redirections**
  - `<` — input from a file
  - `>` — output to a file (truncate)
  - `>>` — output to a file (append)
  - `<<` — heredoc, reading until a delimiter, without adding to the history
- **Pipes** `|` — the output of one command feeds the input of the next
- **Expansions** — `$VAR` for environment variables, `$?` for the exit status of the last foreground command
- **Signals** — `Ctrl-C`, `Ctrl-D` and `Ctrl-\` behave as they do in bash

### Builtins

| Builtin | Description |
| --- | --- |
| `echo` | Prints its arguments, supports the `-n` option |
| `cd` | Changes the working directory (relative or absolute path) |
| `pwd` | Prints the working directory |
| `export` | Sets an environment variable; with no argument, prints the sorted environment |
| `unset` | Removes an environment variable |
| `env` | Prints the environment variables that hold a value |
| `exit` | Leaves the shell, with an optional exit status |

### Bonus

<!-- Tick what is implemented, or delete this section -->

- [ ] Logical operators `&&` and `||`, with parentheses for priority
- [ ] Wildcards `*` in the current directory

## Usage examples

```bash
minishell$ echo "Hello $USER"
Hello theo

minishell$ ls -la | grep ".c" | wc -l
12

minishell$ cat < input.txt > output.txt

minishell$ cat << EOF
> first line
> second line
> EOF
first line
second line

minishell$ export NAME=42
minishell$ echo $NAME
42

minishell$ ls /doesnotexist
ls: cannot access '/doesnotexist': No such file or directory
minishell$ echo $?
2
```

### Exit codes

| Code | Meaning |
| --- | --- |
| `0` | Success |
| `1` | General error |
| `2` | Syntax error |
| `126` | Command found but not executable |
| `127` | Command not found |
| `130` | Terminated by `SIGINT` |
| `131` | Terminated by `SIGQUIT` |

## Technical choices

The line is processed in four stages:

**1. Lexer** — the raw input is split into tokens (words, redirection operators, pipes), while keeping track of open and closed quotes. An unclosed quote is reported as a syntax error.

**2. Parser** — tokens are validated (misplaced operators, redirections without a target) and assembled into a pipeline structure: a list of commands, each holding its own `argv` and its redirections.

**3. Expander** — `$VAR` and `$?` are replaced by their values everywhere except inside single quotes, then the quotes themselves are stripped from the words.

**4. Executor** — for each command: pipe creation, `fork`, redirection setup with `dup2`, binary resolution through the `PATH`, then `execve`. The parent waits for its children and keeps the exit status of the last one.

Builtins run in the parent process when they stand alone, and in a forked child when they are part of a pipeline, so that a builtin such as `cd` can still affect the shell itself.

Every allocation made during a cycle is freed before the prompt is displayed again.

## Project structure

<!-- Replace with your own output of: tree -I 'obj|*.o' -->

```
minishell/
├── Makefile
├── includes/
│   └── minishell.h
├── libft/
├── srcs/
│   ├── main.c
│   ├── lexer/
│   ├── parser/
│   ├── expander/
│   ├── executor/
│   ├── builtins/
│   ├── signals/
│   └── utils/
└── README.md
```

## Resources

### Documentation and references

- `man bash` — the reference for the behaviour we had to reproduce
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — GNU documentation, especially the chapters on shell operation, quoting and expansions
- [GNU Readline Library documentation](https://tiswww.case.edu/php/chet/readline/readline.html) — prompt handling and history
- `man` pages of the allowed functions: `fork`, `execve`, `wait`, `waitpid`, `pipe`, `dup2`, `signal`, `sigaction`, `open`, `unlink`, `stat`, `opendir`
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — the standard grammar of a shell, useful for structuring the parser
- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/) — pipes and inter-process communication
- *Advanced Programming in the UNIX Environment*, W. Richard Stevens — chapters on processes, signals and file descriptors
- [42 Docs — minishell](https://harm-smits.github.io/42docs/projects/minishell) — peer-written overview of the subject

### Use of AI

<!-- REPLACE THIS SECTION WITH WHAT YOU ACTUALLY DID.
     Be specific: which tool, which task, which part of the project.
     Below are example entries in the expected format. -->

AI assistants (Claude, ChatGPT) were used on this project for the following tasks:

- **Understanding concepts**: explanations of how `dup2` and file descriptor inheritance work across `fork`, and of the difference between `signal` and `sigaction`, before writing the corresponding code ourselves.
- **Debugging**: reading error messages and Valgrind reports, and narrowing down where a leak or an invalid read came from.
- **Documentation**: drafting this README file.

No part of the parsing, execution or builtin logic was generated by AI: the architecture and the code were written by us, and every explanation obtained was verified against the `man` pages and bash's actual behaviour before being applied.
