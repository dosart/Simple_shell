#ifndef PROMT_H
#define PROMT_H

#include "wrappers.h"

#include <stdio.h>
#include <unistd.h>

#define MAX_PATH 1024

char *shell_make_promt();

void shell_remove_spaces(char *s);

#endif