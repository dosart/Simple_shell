#include <stdlib.h>

#include "shell.h"
#include "promt.h"

int main()
{
    // Make promt for command line.
    char *promt = shell_make_promt();
    // Run command loop.
    shell_loop(promt);
    free(promt);

    return EXIT_SUCCESS;
}