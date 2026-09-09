#include "libc.h"

void *memcpy(void *dest, const void *src, size_t n)
{
    char *d = (char *)dest;        /* cast de dest */
    const char *s = (const char *)src;  /* cast de src */
    size_t i = 0;

    while (i < n) {
        d[i]=s[i];
        i++;
    }
    return dest;
}