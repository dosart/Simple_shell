#ifndef SHELL_H
#define SHELL_H

#include "global_const.h"
#include "builtin_functions.h"
#include "history.h"
#include "redirect.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SHELL_ARGV_SIZE 64
#define SHELL_TOKENS_DELIMITERS " \t\r\n\a"

typedef struct __pipe_t
{
    int to_close;
    int to_redirect;
    int stream_fd;
} pipe_t;

void shell_set_up_pipe(pipe_t *p);
void shell_close_pipe(pipe_t *p);
int shell_do_pipe(char **argv, int pipe_index);

void shell_loop(char *promt);

char *Shell_read_line();
char *shell_read_line();

void Shell_split_line(char *line, const char *tocken_delimeters, char **argv, size_t argc);
int shell_split_line(char *line, const char *tocken_delimeters, char **argv, size_t argc);

void shell_init_default_value(char **argv, size_t size);

int shell_execute(char **args);
int shell_launch(char **argv);
int shell_create_process(char **argv);

int shell_run_builtin_function(char **argv, size_t i);

#endif