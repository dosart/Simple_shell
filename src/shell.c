#include "shell.h"

history_t global_history;

void shell_loop(char *promt)
{
    char *line;
    int status;
    char *argv[SHELL_ARGV_SIZE];

    shell_init_history(&global_history, MAX_HISTORY);
    do
    {
        printf(SHELL_COLOR_GREEN "%s" SHELL_COLOR_RESET, promt);

        line = Shell_read_line();
        Shell_add_history(&global_history, line);

        // Split line to tokens. Write tokens to argv.
        Shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, SHELL_ARGV_SIZE);

        status = shell_execute(argv);

        shell_init_default_value(argv, SHELL_ARGV_SIZE);
    } while (status);

    shell_free_history(&global_history);
}

char *Shell_read_line()
{
    char *line = shell_read_line();
    if (line == NULL)
    {
        // Logging all errors except Ctrl-D - terminal shutdown
        fprintf(stderr, "[ERROR] Couldn't read from stdin\n");
        exit(EXIT_FAILURE);
    }
    return line;
}

char *shell_read_line()
{
    char *line = NULL;
    size_t size = 0;
    ssize_t str_len;

    // Reading line from stdin
    if ((str_len = getline(&line, &size, stdin)) == -1)
    {
        free(line);
        return NULL;
    }

    // Remove useless \n symbol if exists
    if (line[str_len - 1] == '\n')
    {
        line[str_len - 1] = '\0';
    }
    return line;
}

void Shell_split_line(char *line, const char *tocken_delimeters, char **argv, size_t argc)
{
    int status = shell_split_line(line, tocken_delimeters, argv, argc);
    if (status == -1)
    {

        fprintf(stderr, "[ERROR] Too long string. Count of argument must be <= %li\n", argc);
        free(line);
        exit(EXIT_FAILURE);
    }
}

int shell_split_line(char *line, const char *tocken_delimeters, char **argv, size_t argc)
{
    size_t position = 0;
    char *token;
    // Tokenize process
    token = strtok(line, tocken_delimeters);
    while (token != NULL)
    {
        // Emplace token to array
        argv[position++] = token;
        // If array free space ended
        if (position >= argc)
        {
            return -1;
        }
        // Getting next token
        token = strtok(NULL, tocken_delimeters);
    }

    if (position >= argc)
    {
        return -1;
    }
    // Place NULL to the end of tokens array
    argv[position] = NULL;
    return 0;
}

extern char *global_builtin_name[];
extern int (*global_builtin_func[])(char **);

int shell_execute(char **argv)
{
    if (argv[0] == NULL)
    {
        // If empty command return
        return 1;
    }

    for (size_t i = 0; i < shell_num_builtins(); i++)
    {
        if (strcmp(argv[0], global_builtin_name[i]) == 0)
        {
            return shell_run_builtin_function(argv, i);
        }
    }

    return shell_launch(argv);
}

int shell_run_builtin_function(char **argv, size_t i)
{
    // If redirect exists, do it. Else return
    redirecting_t r = shell_redirect(argv);
    if (!shell_is_redirect(&r))
    {
        return (*global_builtin_func[i])(argv);
    }
    else
    {
        int command_status = (*global_builtin_func[i])(argv);
        int redirect_status = shell_set_default_stream(&r);
        if (command_status == -1 || redirect_status == -1)
            return -1;
        return 1;
    }
}

int shell_is_redirect(redirecting_t *r)
{
    if (r == NULL)
        return 0;

    if (r->saved_fd == -1 || r->stream_fd == -1)
    {
        return 0;
    }
    return 1;
}

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

int shell_launch(char **argv)
{
    int pipe_index;
    if ((pipe_index = shell_find_symbol(argv, "|")) == -1)
    {
        return shell_create_process(argv);
    }
    else
    {
        return shell_do_pipe(argv, pipe_index);
    }
}

int shell_do_pipe(char **argv, int pipe_index)
{
    argv[pipe_index] = NULL;

    int fds[2];
    pipe(fds);

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

    close(fds[0]);
    close(fds[1]);

    wait(NULL);
    wait(NULL);

    return 1;
}

void shell_set_up_pipe(pipe_t *p)
{
    if (p == NULL)
        return;

    close(p->to_close);
    dup2(p->to_redirect, p->stream_fd);
    close(p->to_redirect);
}

int shell_create_process(char **argv)
{
    pid_t child_pid;
    switch (child_pid = fork())
    {
    // Error forking
    case -1:
    {
        perror("[ERROR] shell_launch");
        exit(EXIT_FAILURE);
    }
    // Child process
    case 0:
    {
        // If redirect exists, do it
        shell_redirect(argv);

        // This function must not return control. If returned control, it's an error
        execvp(argv[0], argv);
        perror("[ERROR] shell_launch");
        exit(EXIT_FAILURE);
    }
    // Parent process
    default:
    {
        if (waitpid(child_pid, NULL, 0) != child_pid)
        {
            perror("[ERROR] shell_launch");
            exit(EXIT_FAILURE);
        }
    }
    }
    return 1;
}

void shell_init_default_value(char **argv, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        argv[i] = NULL;
}
