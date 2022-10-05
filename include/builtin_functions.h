#ifndef BUILTIN_FUNCTIONS_H
#define BUILTIN_FUNCTIONS_H

#include "global_const.h"
#include "wrappers.h"
#include "promt.h"

#include <stdio.h>
#include <stdlib.h>

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_clear(char **args);
int shell_pwd(char **args);

size_t shell_num_builtins();

#endif
