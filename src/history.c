#include "history.h"

int shell_init_history(history_t *h, size_t capacity)
{
    if (h == NULL)
        return -1;

    h->history = (char **)malloc(capacity * sizeof(char *));
    h->capacity = capacity;
    h->elem_size = 0;

    if (h->history == NULL)
        return -1;
    else
        return 1;
}

void Shell_add_history(history_t *h, char *command)
{
    int status = shell_add_history(h, command);
    if (status == -1)
    {
        fprintf(stderr, "[ERROR] Shell_add_history: couldn't allocate memory\n");
        exit(EXIT_FAILURE);
    }
}

int shell_add_history(history_t *h, char *command)
{
    if (h == NULL)
        return -1;

    h->history[h->elem_size++] = command;
    if (h->elem_size == h->capacity)
    {
        h->history = (char **)realloc(h->history, (h->capacity * 2) * sizeof(char *));
        h->capacity = h->capacity * 2;

        if (h->history == NULL)
            return -1;
    }
    return 1;
}

void shell_print_history(history_t *h)
{
    if (h == NULL)
        return;
    for (size_t i = 0; i < h->elem_size; i++)
    {
        printf("%s\n", h->history[i]);
    }
}

void shell_free_history(history_t *h)
{
    if (h == NULL)
        return;

    for (size_t i = 0; i < h->elem_size; i++)
    {
        free(h->history[i]);
    }
}