#include "shell.h"

void shell_loop(char *promt)
{
    char *line;

    printf(ANSI_COLOR_GREEN "%s", promt);

    line = shell_read_line();
    if (line != NULL)
        printf("%s\n", line);

    free(line);
}

char *shell_read_line()
{
    char *line = NULL;
    size_t size = 0;
    ssize_t str_len;

    // Reading line from stdin
    if ((str_len = getline(&line, &size, stdin)) == -1)
    {
        // Logging all errors except Ctrl-D - terminal shutdown
        if (errno != 0)
        {
            perror("shell_read_line");
            exit(EXIT_FAILURE);
        }
        free(line);
        printf("\n");
        return NULL;
    }

    // Remove useless \n symbol if exists
    if (line[str_len - 1] == '\n')
    {
        line[str_len - 1] = '\0';
    }

    return line;
}