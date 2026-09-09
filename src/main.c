#include "libc.h"

int main(int argc, char **argv, char **envp)
{

char *buf = malloc(10);
buf[0] = 'A'; buf[1] = 'B'; buf[2] = 'C'; buf[3] = '\0';
printf("avant: %s (%p)\n", buf, buf);

buf = realloc(buf, 200);
printf("apres: %s (%p)\n", buf, buf);   /* doit toujours afficher ABC */

/* cas particuliers */
void *x = realloc(NULL, 50);            /* = malloc */
printf("realloc(NULL,50) = %p\n", x);
void *y = realloc(x, 0);                /* = free */
printf("realloc(x,0) = %p\n", y);       /* doit etre NULL */

  return 0;
}