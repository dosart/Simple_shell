#include "redirect.h"

redirecting_t shell_redirect(char **argv)
{
    redirecting_t result = {.saved_fd = -1, .stream_fd = -1};
    int symbol_index;

    if ((symbol_index = shell_find_symbol(argv, ">")) != -1)
    {
        // If function not builtin the format must be without file.
        // For example {"ls", "ls" "-la" ".", NULL}. Remove symbols (>, >>, <, 2>, 2>>)
        argv[symbol_index] = NULL;
        // Next token should be file name
        return shell_run_redirect(argv[symbol_index + 1], SHELL_OUTPUT, SHELL_DEFAULT_MODE);
    }

    if ((symbol_index = shell_find_symbol(argv, "<")) != -1)
    {
        argv[symbol_index] = NULL;
        return shell_run_redirect(argv[symbol_index + 1], SHELL_INPUT, SHELL_DEFAULT_MODE);
    }

    if ((symbol_index = shell_find_symbol(argv, ">>")) != -1)
    {
        argv[symbol_index] = NULL;
        return shell_run_redirect(argv[symbol_index + 1], SHELL_OUTPUT, SHELL_APPEND_MODE);
    }

    if ((symbol_index = shell_find_symbol(argv, "2>")) != -1)
    {
        argv[symbol_index] = NULL;
        return shell_run_redirect(argv[symbol_index + 1], SHELL_ERROR, SHELL_DEFAULT_MODE);
    }

    if ((symbol_index = shell_find_symbol(argv, "2>>")) != -1)
    {
        argv[symbol_index] = NULL;
        return shell_run_redirect(argv[symbol_index + 1], SHELL_ERROR, SHELL_APPEND_MODE);
    }
    return result;
}

redirecting_t shell_run_redirect(char *file_name, int stream_fd, int mode)
{
    redirecting_t result;
    if (file_name == NULL)
    {
        result.saved_fd = -1;
        result.stream_fd = -1;
    }
    else
    {
        result.saved_fd = shell_do_redirect(file_name, stream_fd, mode);
        result.stream_fd = stream_fd;
    }
    return result;
}

int shell_do_redirect(char *file_name, int stream_fd, int mode)
{
    int saved_fd = dup(stream_fd);
    int fd = open(file_name, shell_get_flag_by_stream(stream_fd, mode), 0666);
    if (fd == -1)
    {
        fprintf(stderr, "[ERROR] Count open file");
        return -1;
    }
    dup2(fd, stream_fd);
    close(fd);

    return saved_fd;
}

int shell_get_flag_by_stream(int stream, int mode)
{
    switch (stream)
    {
    case SHELL_INPUT:
        return O_RDONLY;
    case SHELL_ERROR:
        if (mode == SHELL_DEFAULT_MODE)
        {
            return (O_CREAT | O_WRONLY | O_TRUNC);
        }
        else
        {
            return (O_WRONLY | O_APPEND);
        }
    case SHELL_OUTPUT:
        if (mode == SHELL_DEFAULT_MODE)
        {
            return (O_CREAT | O_WRONLY | O_TRUNC);
        }
        else
        {
            return (O_WRONLY | O_APPEND);
        }
    default:
        return 1;
    }
}

int shell_set_default_stream(redirecting_t *r)
{
    if (r == NULL)
        return -1;

    FILE *stream;
    stream = shell_get_stream_by(r->stream_fd);
    if (stream == NULL)
    {
        fprintf(stderr, "[ERROR] Coudn't write to %i stream", r->stream_fd);
        return -1;
    }
    fflush(stream);

    dup2(r->saved_fd, r->stream_fd);
    close(r->saved_fd);

    return 1;
}

FILE *shell_get_stream_by(int stream_fd)
{
    switch (stream_fd)
    {
    case SHELL_INPUT:
        return stdin;
    case SHELL_OUTPUT:
        return stdout;
    case SHELL_ERROR:
        return stderr;
    case SHELL_APPEND:
        return stdout;
    default:
        return NULL;
    }
}