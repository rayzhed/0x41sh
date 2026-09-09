#include "libc.h"


/* Note: ne gere pas INT_MIN (-num deborde). Suffisant pour l'instant mais à fix plus tard si bug rencontrer. */
int puthex(unsigned long num)
{
    int n = 0;
    char digits[] = "0123456789abcdef";


    if (num < 16){
        putchar(digits[num]);
        n++;
        return n;
    }

    n += puthex(num / 16);
    putchar(digits[num % 16]);
    n++;
    
    return n;
}