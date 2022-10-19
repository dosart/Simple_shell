#ifndef PROMT_H
#define PROMT_H

#include "wrappers.h"
#include "utils.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SHELL_MAX_PATH 1024

char *shell_make_promt();

char *shell_make_new_promt(char *old_promt);

#endif