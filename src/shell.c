#include "shell.h"

history_t global_history;

void shell_loop()
{
    char *line;
    char *promt;
    int status;
    char *argv[SHELL_ARGV_SIZE];

    shell_init_history(&global_history, MAX_HISTORY);

    // Make promt for command line.
    promt = shell_make_promt();
    do
    {
        printf(SHELL_COLOR_GREEN "%s" SHELL_COLOR_RESET, promt);

        line = Shell_read_line();
        Shell_add_history(&global_history, line);

        // Split line to tokens. Write tokens to argv.
        Shell_split_line(line, SHELL_TOKENS_DELIMITERS, argv, SHELL_ARGV_SIZE);

        status = shell_execute(argv);

        shell_init_default_value(argv, SHELL_ARGV_SIZE);

        // If prompt was changed(for example cd command), make new prompt
        promt = shell_make_new_promt(promt);
    } while (status);

    shell_free_history(&global_history);
    free(promt);
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
