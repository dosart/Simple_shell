#ifndef HISTORY_H
#define HISTORY_H

#include <stdlib.h>
#include <stdio.h>

typedef struct __history_t
{
    char **history;
    size_t capacity;
    size_t elem_size;

} history_t;

int shell_init_history(history_t *h, size_t capacit);

void Shell_add_history(history_t *h, char *command);

int shell_add_history(history_t *h, char *command);

void shell_print_history(history_t *h);

void shell_free_history(history_t *h);

#endif