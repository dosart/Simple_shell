#include "pipe.h"

int shell_do_pipe(char **argv, int pipe_index)
{
    argv[pipe_index] = NULL;

    int fds[2];
    Pipe(fds);

    pipe_t first_children = {.to_close = fds[0], .to_redirect = fds[1], 1};
    pipe_t second_children = {.to_close = fds[1], .to_redirect = fds[0], 0};

    if (fork() == 0)
    {

        shell_set_up_pipe(&first_children);
        execvp(argv[0], argv);
    }

    if (fork() == 0)
    {
        // If redirect exists, do it. Else return
        shell_redirect(&argv[pipe_index + 1]);

        shell_set_up_pipe(&second_children);
        execvp(argv[pipe_index + 1], &argv[pipe_index + 1]);
    }

    Close(fds[0]);
    Close(fds[1]);

    Wait(NULL);
    Wait(NULL);

    return 1;
}

void shell_set_up_pipe(pipe_t *p)
{
    if (p == NULL)
        return;

    Close(p->to_close);
    Dup2(p->to_redirect, p->stream_fd);
    Close(p->to_redirect);
}