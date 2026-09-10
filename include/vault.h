#ifndef VAULT_H
#define VAULT_H
#include "libc.h"

#define MAX_LEN 64
#define VAULT_INITIAL_CAPACITY 8
#define CANARY 0x3078343153482121ULL /* "0x41SH!!" */

struct entry {
    char name[MAX_LEN];
    char user[MAX_LEN];
    char password[MAX_LEN];
};
typedef struct entry t_entry;

struct vault {
    struct entry *entries;
    size_t count;
    size_t capacity;
};
typedef struct vault t_vault;

int vault_init(t_vault *vault);

int vault_add(t_vault *vault, const char *name, const char *user, const char *password);

void vault_list(t_vault *vault);

t_entry *vault_get(t_vault *vault, const char *name);


int vault_save(t_vault *vault, const char *filename, const char *master);

int vault_load(t_vault *vault, const char *filename, const char *master);

void vault_free(t_vault *vault);

#endif