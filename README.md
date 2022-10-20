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
