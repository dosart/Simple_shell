#include "wrappers.h"

int Gethostname(char *name, size_t len)
{
    int status = gethostname(name, len);
    if (status != 0)
    {
        errno = status;
        perror("gethostname");
        return -1;
    }
    return status;
}

char *Getcwd(char *buf, size_t size)
{
    char *status = getcwd(buf, size);
    if (status == NULL)
    {
        perror("getcwd");
        return status;
    }
    return status;
}

int Getlogin_r(char *name, size_t len)
{
    int status = getlogin_r(name, len);
    if (status != 0)
    {
        errno = status;
        perror("getlogin_r");
        return -1;
    }
    return status;
}

int Dup2(int old_fd, int new_fd)
{
    int status = dup2(old_fd, new_fd);
    if (status == -1)
    {
        errno = status;
        perror("dup2");
        return -1;
    }
    return status;
}

int Dup(int old_fd)
{
    int status = dup(old_fd);
    if (status == -1)
    {
        errno = status;
        perror("dup");
        return -1;
    }
    return status;
}

int Close(int fd)
{
    int status = close(fd);
    if (status == -1)
    {
        errno = status;
        perror("close");
        return -1;
    }
    return status;
}

pid_t Wait(int *st)
{
    pid_t status = wait(st);
    if (status == -1)
    {
        errno = status;
        perror("wait");
        return -1;
    }
    return status;
}

int Pipe(int filedes[2])
{
    int status = pipe(filedes);
    if (status != 0)
    {
        errno = status;
        perror("pipe");
        return -1;
    }
    return status;
}