#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

void shell_remove_spaces(char *s);

int shell_find_symbol(char **str, const char *symbol);

#endif