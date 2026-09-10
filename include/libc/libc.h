/* prototypes et types de ma mini libc */
#ifndef LIBC_H
#define LIBC_H

#define NULL ((void *)0)

//help: flags for open
#define O_RDONLY  0
#define O_WRONLY  1
#define O_RDWR    2
#define O_CREAT   00000100
#define O_TRUNC   00001000
#define O_APPEND  00002000

typedef unsigned long long size_t;
typedef long long ssize_t;
typedef unsigned int umode_t;

struct header {
    size_t size;
    struct header *next;
    struct header *prev;
    int isFree;
};
typedef struct header t_header;

extern void * HEAP_START;
extern void * HEAP_END;


ssize_t write(int fd, const void *buf, size_t count);

int putchar(char c);

int puts(const char *str);

int putnbr(int num);

int puthex(unsigned long num);

int strcmp(const char *s1, const char *s2);

int strncmp(const char *s1, const char *s2, size_t n);

char *strncpy(char *dest, const char *src, size_t n);

ssize_t read(int fd, void *buf, size_t count);

ssize_t getline(char **lineptr, size_t *n, int fd);

[[noreturn]] void exit(int status);

int printf(const char *format, ...);

void *brk(void *addr);

void *sbrk(int size);

void *malloc(size_t size);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

void *memcpy(void *dest, const void *src, size_t n);

int open(const char *filename, int flags, umode_t mode);

int rename(const char *oldpath, const char *newpath);

int close(int fd);

size_t strlen(const char *s);

void xtea(void *data, size_t size, const char *password, int decrypt);

#endif