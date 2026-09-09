#include "libc.h"

int putchar(char c)
{
    ssize_t ret = write(1, &c, 1);
    if (ret < 0)
        return -1;
    return c;
}