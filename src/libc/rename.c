#include "libc.h"

int rename(const char *oldpath, const char *newpath){
    int ret;
    __asm__ volatile (
        "mov %1, %%rdi\n"   // oldpath
        "mov %2, %%rsi\n"   // newpath
        "mov $82, %%rax\n"   // rename

        "syscall\n"
        : "=a"(ret)
        : "r"(oldpath), "r"(newpath)
        : "rdi", "rsi"
    );
    return ret;
}
