#include "builtin_functions.h"

char *builtin_name[] = {
    "cd",
    "help",
    "exit",
    "clear",
    "pwd"};

int (*builtin_func[])(char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit,
    &shell_clear,
    &shell_pwd};

size_t shell_num_builtins()
{
    return sizeof(builtin_name) / sizeof(char *);
}

int shell_cd(char **args)
{
    // Allow for using empty "cd" to change to home directory
    if (args[1] == NULL)
    {
        char *home = getenv("HOME");
        if (home == NULL)
        {
            fprintf(stderr, "[ERROR] HOME environment variable not set. Home directory commands will not work\n");
            return 0;
        }
        if (chdir(home) == -1)
        {
            perror("[ERROR]");
            return 0;
        }
    }
    // Else change the directory to the one specified by
    else
    {
        if (chdir(args[1]) == -1)
        {
            perror("[ERROR]");
            return 0;
        }
    }
    return 1;
}

int shell_help(char **args)
{
    (void)args;
    printf(SHELL_COLOR_GREEN "----------Help--------" SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Not all the internal commands are supported." SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Supported internal commands: cd, pwd, echo, exit " SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Commands can be piped together(more than 1 pipe is allowed also)." SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Ex. ls -a | wc -c is allowed" SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Asyncronous commands are allowed(more than 2 are allowed too) " SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Ex. ls -a & cat file && cat file2 is allowed" SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Output redirection to file is supported: ex. ls > fileOutput " SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Output redirection to file with append is supported: ex. ls >> fileOutput " SHELL_COLOR_RESET "\n");
    printf(SHELL_COLOR_GREEN "Input redirection from file is supported: ex. wc -c < fileInput " SHELL_COLOR_RESET "\n");

    return 1;
}

int shell_exit(char **args)
{
    (void)args;
    return 0;
}

int shell_clear(char **args)
{
    (void)args;
    system("clear");
    return 1;
}

int shell_pwd(char **args)
{
    (void)args;
    char current_dir[SHELL_MAX_PATH] = "";
    Getcwd(current_dir, SHELL_MAX_PATH);
    shell_remove_spaces(current_dir);

    printf("%s\n", current_dir);
    return 1;
}