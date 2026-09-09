#include "libc.h"

int main(int argc, char **argv, char **envp)
{

int x = 42;
printf("adresse: %p\n", &x);

printf("100%z fin\n");                    /* attendu : 100%z fin */
printf("abc%");                           /* ne doit pas planter */
printf("\n%d %s %c %p\n", 42, "test", 'X', &x);
  

  return 0;
}