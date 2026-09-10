SRCS = $(wildcard src/libc/*.c)
LIBC_OBJS = $(patsubst src/libc/%.c, build/src/libc/%.o, $(SRCS))
OBJS = build/crt0.o build/src/main.o $(LIBC_OBJS) $(VAULT_OBJS)

VAULT_SRCS = $(wildcard src/vault/*.c)
VAULT_OBJS = $(patsubst src/vault/%.c, build/src/vault/%.o, $(VAULT_SRCS))


0x41sh: $(OBJS)
	ld -e _start -o 0x41sh $(OBJS)

build/crt0.o: crt0.asm
	nasm -f elf64 crt0.asm -o build/crt0.o

build/src/main.o: src/main.c
	gcc -c -Iinclude/libc -Iinclude -fno-stack-protector src/main.c -o build/src/main.o

build/src/libc/%.o: src/libc/%.c
	gcc -c -fno-stack-protector -Iinclude/libc -Iinclude $< -o $@

build/src/vault/%.o: src/vault/%.c
	gcc -c -fno-stack-protector -Iinclude/libc -Iinclude $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f 0x41sh

re: fclean 0x41sh

.PHONY: clean fclean re

