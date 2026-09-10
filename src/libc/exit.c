#include "libc.h"

[[noreturn]] void exit(int status){
    __asm__ volatile (
        "mov %0, %%rdi\n"   // status
        "mov $60, %%rax\n"   // syscall: exit
        "syscall\n"
        :
        : "r"((long)status)
        : "rax", "rdi"
    );
}