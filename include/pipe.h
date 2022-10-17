#ifndef PIPE_H
#define PIPE_H

#include "redirect.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct __pipe_t
{
    int to_close;
    int to_redirect;
    int stream_fd;
} pipe_t;

void shell_set_up_pipe(pipe_t *p);
void shell_close_pipe(pipe_t *p);
int shell_do_pipe(char **argv, int pipe_index);

#endif