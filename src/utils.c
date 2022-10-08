#include "utils.h"

void shell_remove_spaces(char *s)
{
    if (s == NULL)
        return;
    char *d = s;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    } while ((*s++ = *d++));
}

int shell_find_symbol(char **str, const char *symbol)
{
    if (str == NULL || symbol == NULL)
        return -1;

    int index = 0;
    while (*str != NULL)
    {
        if (strcmp(*str, symbol) == 0)
            return index;
        str++;
        index++;
    }
    return -1;
}