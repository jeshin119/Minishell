
# 42-minishell

The objective of this project is to create a simple shell, like an own little bash.<br>
It is the first group project in the 42 core curriculum. 

## Project specifications

For the project we were allowed to use GNU's readline library which handles the terminal interaction (history & input reading).
For everything else the subject allows only to use a few low-level functions and a few POSIX system calls.

<b>Allowed functions:</b>
```readline, rl_clear_history, rl_on_new_line,rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read,close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs```

## Features

### Basics:
- History of previous entered commands
- Search and launch the right executable (based on the PATH variable, using a relative or an absolute path)
- Environment variables ($ followed by a sequence of characters) expand to their values
- Wildcards * in the current working directory
- ctrl-C, ctrl-D and ctrl-\ behave like in bash
- ```’``` (single quotes - prevent from interpreting meta-characters in quoted sequence)
- ```"``` (double quotes - prevent from interpreting meta-characters in quoted sequence except for $)
- ```$?``` expands to the last exit status
- ```|``` connect cmds or groups with pipes; output of a cmd is connected to the input of the next cmd via a pipe
- ```&&``` and ```||``` with parenthesis for priorities

### Builtins:
- ```echo``` with option -n
- ```cd``` (relative or absolute path, ```-``` for OLDPWD, without arg for HOME)
- ```pwd``` without options
- ```export``` without options
- ```unset``` without options
- ```env``` without options
- ```exit [exit_status]``` without options

### Redirections:

```[n]``` (optional) specifies the file descriptor, if not specified it is stdout/stdin

- ```[n]< file``` Redirecting Input
- ```[n]<< limiter``` Here Documents
- ```[n]> file``` Redirecting Output
- ```[n]>> file``` Appending Redirected Output


## Dependencies
### Install readline with [brew](https://brew.sh/)
```
brew install readline
```

```
brew link --force readline
```

Add the path to the lib

Replace ~/.zshrc with ~/.bashrc if you use bash instead of zsh
```
echo 'export C_INCLUDE_PATH="/usr/local/opt/readline/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```
```
echo 'export LIBRARY_PATH="/usr/local/opt/readline/lib:$LIBRARY_PATH"' >> ~/.zshrc
```
```
source ~/.zshrc
```

### Install readline on 42 Macs

Install Brew, <b>only if it is not already installed:</b>

```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```

Install Readline library:
```
brew install readline
```

```
brew link --force readline
```

```
echo 'export C_INCLUDE_PATH="$HOME/.brew/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```

```
echo 'export LIBRARY_PATH="$HOME/.brew/lib:$LIBRARY_PATH"' >> ~/.zshrc
```
```
source ~/.zshrc
```

> #### Sample restrictions:
> - All variables have to be declared and aligned at the top of each function
> - Each function can not have more then 25 lines
> - Projects should be created with allowed std functions otherwise it is cheating
