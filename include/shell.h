#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>

/*
Use these colors to print colored text on the console
*/
#define ANSI_COLOR_GREEN "\x1b[32m"

void shell_loop(char *promt);

#endif