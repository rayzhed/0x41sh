#include "libc.h"

int printf(const char *format, ...){
    __builtin_va_list args;
    __builtin_va_start(args, format);
    char *s;
    int n = 0;

    while(*format != '\0'){
        /* % est manger il faut fix pour qu'il soit afficher */
        if(*format == '%'){
            format++;
            switch(*format++){
                case 's':
                {
                    s = __builtin_va_arg(args, char *);
                    while (*s != '\0'){
                        putchar(*s);
                        s++;
                        n++;
                    }
                    break;
                }
                case 'd':
                {
                    n += putnbr(__builtin_va_arg(args, int));
                    break;
                }
                case 'c': 
                {
                    putchar((char) __builtin_va_arg(args, int));
                    n++;
                    break;
                }
                default:
                {
                    if(*format == '\0')
                        break;
                    else
                        putchar(*format);
                }
            }

        } else {
            putchar(*format);
            format++;
            n++;
        }
    }
    
    __builtin_va_end(args);
    return n;
}