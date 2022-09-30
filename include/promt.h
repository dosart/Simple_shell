#ifndef PROMT_H
#define PROMT_H

#include <stdio.h>
#include <unistd.h>

#define MAX_PATH 1024

char *shell_make_promt();

void remove_spaces(char *s);

#endif