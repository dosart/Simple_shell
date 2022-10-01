#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/*
Use these colors to print colored text on the console
*/
#define ANSI_COLOR_GREEN "\x1b[32m"

void shell_loop(char *promt);

char *shell_read_line();

#endif