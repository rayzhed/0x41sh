#include "libc.h"

size_t brk(void *addr){
    size_t ret;
    __asm__ volatile (
        "mov $12, %%rax\n"   // syscall: read
        "mov %1, %%rdi\n"   // brk
        "syscall\n"
        : "=a"(ret)
        : "r"(addr)
        : "rdi"
    );
    return ret;
}