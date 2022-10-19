#include "promt.h"

#include <stdlib.h>
#include <string.h>

static char host_name[SHELL_MAX_PATH] = "";

static char saved_dir[SHELL_MAX_PATH] = "";

static char user_name[SHELL_MAX_PATH] = "";

char *shell_make_promt()
{
    Gethostname(host_name, SHELL_MAX_PATH);

    Getcwd(saved_dir, SHELL_MAX_PATH);

    Getlogin_r(user_name, SHELL_MAX_PATH);

    size_t needed_mem = (size_t)snprintf(NULL, 0, "%s@%s %s > ", user_name, host_name, saved_dir) + sizeof('\0');
    char *promt = malloc(needed_mem);
    snprintf(promt, needed_mem, "%s@%s %s > ", user_name, host_name, saved_dir);

    return promt;
}

char *shell_make_new_promt(char *old_promt)
{
    char current_dir[SHELL_MAX_PATH] = "";
    Getcwd(current_dir, SHELL_MAX_PATH);

    if (strcmp(saved_dir, current_dir) == 0)
        return old_promt;
    else
    {
        free(old_promt);
        size_t needed_mem = (size_t)snprintf(NULL, 0, "%s@%s %s > ", user_name, host_name, current_dir) + sizeof('\0');
        char *new_promt = malloc(needed_mem);
        snprintf(new_promt, needed_mem, "%s@%s %s > ", user_name, host_name, current_dir);

        strcpy(saved_dir, current_dir);
        return new_promt;
    }
}