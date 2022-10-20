# Simple shell

**Simple shell** - it's a simple pet project for simulates the working of command line interface in Unix-like environment. 
Implemented functionalities are as under:
 - execute all the external commands (ls, wc, etc.);

 - implement internal commands: cd, pwd, history, clear, help, exit;

 - redirection operators: STDIN, STDOUT, STDERR (>>,>,<<,<,2>);

- support for history command;

- pipes | (single) (Ex: ls | grep 'a');

## Technologies:

 - c - a programming language;
 - make - an automation tool;
 - valgrind - an instrumentation framework for building dynamic analysis tools;

 ## Install:

```
 $ git clone https://github.com/dosart/Simple_shell.git
 $ make run
 ```
 ## Examples
 
```
 $ run command ls -la .
```
 [![asciicast](https://asciinema.org/a/tEYPEj6vGMsvwt5uWjKcFPkxM.svg)](https://asciinema.org/a/tEYPEj6vGMsvwt5uWjKcFPkxM)
 
run builtin function

```
 $ pwd
 $ cd ..
```

[![asciicast](https://asciinema.org/a/cJasAKKxWPS4gJrEIj3nUlSB0.svg)](https://asciinema.org/a/cJasAKKxWPS4gJrEIj3nUlSB0)

Pipes and redirects

```
 $ ls -la . | wc -c
 $ ls -la | wc -c > 1.txt
 $ ls -la | wc -c >> 1.txt
```

[![asciicast](https://asciinema.org/a/hmpjBkjfyzmqe8m9S2rs0lGRv.svg)](https://asciinema.org/a/hmpjBkjfyzmqe8m9S2rs0lGRv)
