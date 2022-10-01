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