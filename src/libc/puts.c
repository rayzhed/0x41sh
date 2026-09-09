#include "libc.h"

int puts(const char *str)
{
    while (*str != '\0')
    {
        if (putchar(*str) < 0)
            return -1;
        str++;
    }
    if (putchar('\n') < 0)
        return -1;
    return 0;
}