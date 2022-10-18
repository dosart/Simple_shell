#ifndef REDIRECT_H
#define REDIRECT_H

#include "global_const.h"
#include "utils.h"
#include "wrappers.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct __redirecting_t
{
    int saved_fd;
    int stream_fd;

} redirecting_t;

int shell_is_redirect(redirecting_t *r);

int shell_do_redirect(char *file_name, int stream_fd, int mode);
int shell_set_default_stream(redirecting_t *r);
int shell_get_flag_by_stream(int stream, int mode);
FILE *shell_get_stream_by(int stream_fd);

redirecting_t shell_redirect(char **argv);
redirecting_t shell_run_redirect(char *file_name, int stream_fd, int mode);

#endif
