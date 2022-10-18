#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int Gethostname(char *name, size_t len);

char *Getcwd(char *buf, size_t size);

int Getlogin_r(char *name, size_t namesize);

int Dup2(int old_fd, int new_fd);

int Dup(int old_fd);

int Close(int fd);

pid_t Wait(int *st);

int Pipe(int filedes[2]);

#endif