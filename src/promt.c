#include "promt.h"

#include <stdlib.h>
#include <string.h>

char *shell_make_promt()
{
    char host_name[SHELL_MAX_PATH] = "";
    Gethostname(host_name, SHELL_MAX_PATH);
    shell_remove_spaces(host_name);

    char current_dir[SHELL_MAX_PATH] = "";
    Getcwd(current_dir, SHELL_MAX_PATH);
    shell_remove_spaces(current_dir);

    char user_name[SHELL_MAX_PATH] = "";
    Getlogin_r(user_name, SHELL_MAX_PATH);
    shell_remove_spaces(user_name);

    size_t needed_mem = (size_t)snprintf(NULL, 0, "%s@%s %s > ", user_name, host_name, current_dir) + sizeof('\0');
    char *promt = malloc(needed_mem);
    snprintf(promt, needed_mem, "%s@%s %s > ", user_name, host_name, current_dir);

    return promt;
}