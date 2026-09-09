#include "libc.h"

int main(int argc, char **argv, char **envp)
{

void *a = malloc(30);
void *b = malloc(50);
void *c = malloc(100);
printf("a=%p b=%p c=%p\n", a, b, c);

t_header *cur = (t_header *)HEAP_START;
while (cur != NULL) {
    printf("bloc %p size=%d\n", (void *)cur, (int)cur->size);
    cur = cur->next;
}
  return 0;
}