*This project has been created as part of the 42 curriculum by sabytheo and egache.*

# minishell

> *As beautiful as a shell*

## Description

**minishell** is a minimalistic reimplementation of a Unix shell, written in C and inspired by **bash**.

The goal of the project is to understand how a command interpreter works under the hood: how a raw line of text becomes a running process. Building it means dealing with process creation and synchronisation, file descriptor manipulation, environment handling and signal management — all of it directly on top of the system calls, without any external help beyond `readline`.

The program displays a prompt, reads a line, splits it into typed tokens, expands the variables it contains, regroups everything into a list of commands with their redirections, and finally executes them. It supports pipes, the four redirection types, quoting rules, environment variables, the seven required builtins, and it reproduces bash's behaviour for interactive signals and exit codes.

Beyond the subject, the shell also runs in **script mode**: given a file as its single argument, it reads and executes it line by line instead of opening an interactive prompt.

In accordance with the subject, the program uses a **single global variable**, `g_signal_value`, declared `volatile sig_atomic_t` and used only to carry the number of a received signal. No other state passes through it.

## Instructions

### Requirements

- `gcc` or `clang`
- `make`
- The **readline** library and its headers

```bash
# Debian / Ubuntu
sudo apt install libreadline-dev
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
| `make run` | Builds, then runs the shell under Valgrind, sending its report to a listener |
| `make valgrind` | Starts the Valgrind listener on port 4242 — run it in another terminal, then `make run` |

The project is compiled with `-Wall -Wextra -Werror -g3` and links against its own Libft, which also provides `ft_printf` and `get_next_line`.

### Execution

```bash
./minishell              # interactive prompt
./minishell script.sh    # runs the file line by line
```

`exit` or `Ctrl-D` leaves the shell. Passing more than one argument is refused.

Since `readline()` allocates memory the program cannot free, a suppression file is provided at the root of the repository and used by the Valgrind targets:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
         --suppressions=ignore_readline.supp ./minishell
```

## Features

- **Interactive prompt** with a working history
- **Executable lookup** through the `PATH`, or by relative / absolute path
- **Quoting**: single quotes prevent any interpretation, double quotes allow variable expansion
- **Redirections**: `<`, `>`, `>>` and heredoc `<<`, several of them per command
- **Pipes** `|`, with no limit on the number of commands in the chain
- **Expansions**: `$VAR` and `$?`
- **Signals**: `Ctrl-C`, `Ctrl-D` and `Ctrl-\` behave as they do in bash, at the prompt, during a command and inside a heredoc
- **`SHLVL`** is incremented when the shell starts, as bash does

### Builtins

| Builtin | Description |
| --- | --- |
| `echo` | Prints its arguments, supports the `-n` option |
| `cd` | Changes the working directory and updates `PWD` and `OLDPWD` |
| `pwd` | Prints the working directory |
| `export` | Sets a variable after checking the identifier is valid; with no argument, prints the variables kept in the export list |
| `unset` | Removes a variable from the environment |
| `env` | Prints the variables that hold a value |
| `exit` | Leaves the shell, with an optional exit status |

## Usage examples

```bash
Minishell>echo "Hello $USER"
Hello tsaby

Minishell>ls -la | grep ".c" | wc -l
12

Minishell>cat < input.txt > output.txt

Minishell>cat << EOF
> first line
> second line
> EOF
first line
second line

Minishell>export NAME=42
Minishell>echo $NAME
42

Minishell>ls /doesnotexist
minishell: '/doesnotexist': No such file or directory
Minishell>echo $?
127
```

### Exit codes

| Code | Meaning |
| --- | --- |
| `0` | Success |
| `1` | General error |
| `126` | Found but not executable — permission denied, or not a regular file |
| `127` | Command not found |
| `128 + n` | Terminated by signal `n` — `130` for `Ctrl-C`, `131` for `Ctrl-\` |

## Technical choices

**Tokenizing** — the line is first checked for unbalanced quotes, which is the one syntax error that can be detected before anything is cut. It is then walked once, producing a linked list of tokens, each carrying its value and a type among `T_WORD`, `T_PIPE`, `T_REDIR_IN`, `T_REDIR_OUT`, `T_APPEND` and `T_HEREDOC`. A second pass validates the sequence: an operator with nothing to work on, a pipe in the wrong place, a redirection without a target.

**Expanding** — each token value is rewritten by a small state machine that walks it character by character while tracking whether it currently sits inside single or double quotes. A `$` followed by a letter, an underscore or a `?` triggers a lookup; anything else is copied as is. The quote characters themselves are consumed by that same walk, so a token that needed expansion comes out already unquoted. Tokens that contain no `$` skip the machine entirely and go through a dedicated quote-stripping function instead.

**Building the commands** — two cursors walk the token list in parallel, one collecting the words that make up `argv`, the other collecting redirections. Each redirection is stored as a duplicated pair — the operator and its target — in a list attached to the command, so a command can carry as many redirections as it needs and the executor never has to look back at the original token list.

**Heredocs** — every heredoc in the line is read *before* any process is forked, and written to a temporary file named `.heredoc_tmp_N`. The redirection target is then rewritten to point at that file, which turns a heredoc into an ordinary input redirection for the rest of the pipeline. Interrupting a heredoc with `Ctrl-C` relies on `rl_event_hook`: the handler raises the global signal value, the hook sees it and sets `rl_done`, which makes `readline()` return instead of waiting forever. All temporary files are unlinked once the command has run, and on the interrupted path too.

**Executing** — a single command and a pipeline take two different routes. Alone, a builtin runs in the parent process, with the standard input and output saved beforehand and restored afterwards, so that `cd`, `export` and `unset` actually affect the shell. In a pipeline, the `n - 1` pipes are created up front, one `fork` is issued per command, each child duplicates the right ends onto its standard descriptors, closes every pipe descriptor it does not use, applies its own redirections, and either runs the builtin or calls `execve`. The parent then waits for all of them and keeps the status of the pipeline.

**Exit status** — the status returned by `waitpid` is decoded through `WIFEXITED` and `WIFSIGNALED`, so a command killed by a signal reports `128 + signal` exactly like bash. That value is what `$?` reads.

**Environment** — the environment is kept as a linked list, with a second list for the variables added by `export` that have no value yet. It is flattened back into a `char **` table only when `execve` needs one.

**Signals** — `sigaction` is used rather than `signal`, and `ECHOCTL` is cleared through `termios` so that `^C` is not echoed to the terminal. Handlers are swapped depending on the context: interactive prompt, command running, or heredoc.

**Cleanup** — freeing is split by scope: what belongs to one command cycle, what belongs to a child process, and what belongs to the shell itself. Any allocation failure anywhere in the chain routes to the same exit path, which frees the lists, the environment, the pipes and the heredoc files before leaving.

## Project structure

```
minishell/
├── Makefile
├── ignore_readline.supp        # Valgrind suppressions for readline
├── includes/
│   ├── minishell.h             # main structure and prototypes
│   ├── token.h                 # token and command types
│   ├── expand.h                # expander state
│   └── error.h                 # error messages
└── sources/
    ├── main.c                  # loop, prompt, launch modes
    ├── init.c, init_envp.c     # startup, environment, SHLVL
    ├── tokens.c                # quote check, tokenizing, formatting
    ├── define_tokens_utils.c   # token extraction and typing
    ├── format_tokens_utils.c   # quote removal
    ├── check_tokens.c          # syntax validation
    ├── expand.c, expand_utils.c
    ├── exec_tokens.c           # tokens to commands and redirections
    ├── check_cmd.c             # command resolution and error codes
    ├── find_path.c             # PATH lookup
    ├── exec_single.c           # single command
    ├── exec_pipes.c            # pipelines
    ├── exec_builtins.c         # builtin dispatch
    ├── setup_redirections.c
    ├── heredoc.c, heredoc_utils.c
    ├── signals.c, signals_handler.c
    ├── chainedlst_totab.c      # environment list to char **
    ├── clean*.c                # freeing by scope
    ├── debug.c                 # token and command dumps
    └── builtins/               # echo, cd, pwd, env, export, unset, exit
```

## Resources

### Documentation and references

- `man bash` — the reference for the behaviour to reproduce, and the source of truth every time our output differed from bash's
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — in particular the chapters on quoting, expansions and exit status
- [GNU Readline Library documentation](https://tiswww.case.edu/php/chet/readline/readline.html) — the prompt, the history, and `rl_event_hook` / `rl_done`, without which a heredoc cannot be interrupted
- `man` pages of the allowed functions: `fork`, `execve`, `waitpid`, `pipe`, `dup2`, `sigaction`, `open`, `unlink`, `stat`, `access`, `tcsetattr`
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — the standard grammar, used to structure the token types
- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/) — pipes and inter-process communication
- [42 Docs — minishell](https://harm-smits.github.io/42docs/projects/minishell) — peer-written overview of the subject
- Valgrind documentation, for `--track-fds` and the suppression file format

