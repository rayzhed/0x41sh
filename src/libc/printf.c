#include "libc.h"

int printf(const char *format, ...){
    __builtin_va_list args;
    __builtin_va_start(args, format);
    char *s;
    int n = 0;

    while(*format != '\0'){
        if(*format == '%'){
            format++;
            if (*format == '\0'){
                putchar('%');
                n++;
                break;
            }
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
                case '%':
                {
                    putchar('%');
                    n++;
                    break;
                }
                case 'p':
                {
                    n += puthex((unsigned long) __builtin_va_arg(args, void *));
                    break;
                }
                default:
                {
                    putchar('%');
                    putchar(*(format - 1));
                    n += 2;
                    break;
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