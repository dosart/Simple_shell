#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int Gethostname(char *name, size_t len);

char *Getcwd(char *buf, size_t size);

int Getlogin_r(char *name, size_t namesize);

#endif