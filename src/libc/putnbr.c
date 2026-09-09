#include "libc.h"


/* Note: ne gere pas INT_MIN (-num deborde). Suffisant pour l'instant mais à fix plus tard si bug rencontrer. */
int putnbr(int num)
{
    int n = 0;

    if (num < 0){
        putchar('-');
        num = -num;
        n++;
    }


    if (num < 10){
        putchar(num + '0');
        n++;
        return n;
    }

    n += putnbr(num / 10);
    putchar('0' + num % 10);
    n++;
    
    return n;
}