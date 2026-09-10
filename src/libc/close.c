#include "libc.h"

int close(int fd){
    int ret;
    __asm__ volatile (
        "mov %1, %%rdi\n"   // fd
        "mov $3, %%rax\n"   // close

        "syscall\n"
        : "=a"(ret)
        : "r"((long)fd)
        : "rdi"
    );
    return ret;
}