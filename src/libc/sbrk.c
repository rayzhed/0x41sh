#include "libc.h"

size_t sbrk(int size){
   size_t ret = brk(HEAP_END+size);

   return ret;
}