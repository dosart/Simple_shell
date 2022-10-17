#ifndef GLOBAL_CONST_H
#define GLOBAL_CONST_H

// Use these colors to print colored text on the console
#define SHELL_COLOR_GREEN "\x1b[32m"
#define SHELL_COLOR_RED "\x1b[31m"
#define SHELL_COLOR_BLUE "\x1b[34m"
#define SHELL_COLOR_RESET "\x1b[0m"

#define MAX_HISTORY 64

#define SHELL_INPUT 0
#define SHELL_OUTPUT 1
#define SHELL_ERROR 2
#define SHELL_APPEND 3

#define SHELL_DEFAULT_MODE 0
#define SHELL_APPEND_MODE 1

#define SHELL_ARGV_SIZE 64
#define SHELL_TOKENS_DELIMITERS " \t\r\n\a"

#endif