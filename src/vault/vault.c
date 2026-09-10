#include "libc.h"
#include "vault.h"

/*Vault iniiiiiiit*/
int vault_init(t_vault *vault){
    vault->entries = malloc(8 * sizeof(t_entry));
    if (vault->entries == NULL){
        return -1;
    }
    vault -> count = 0;
    vault -> capacity = 8;


    return 0;
}

/*Vault Helper*/
static void copy_field(char *dest, const char *src){
    size_t len = strlen(src);
    if (len >= MAX_LEN)
        len = MAX_LEN - 1;
    memcpy(dest, src, len);
    dest[len]= '\0';
}

/*+1 entrée à gérer pour vault :}*/
int vault_add(t_vault *vault, const char *name, const char *user, const char *password){
    if (vault->count == vault->capacity){
        size_t cap = vault->capacity * 2;
        t_entry *tmp = realloc(vault->entries, cap * sizeof(t_entry));
        if (tmp == NULL)
            return -1;
        vault->entries = tmp;
        vault->capacity = cap;

    }

    t_entry *e = &vault->entries[vault->count];

    copy_field(e->name, name);
    copy_field(e->user, user);
    copy_field(e->password, password);

    vault->count++;

    return 0;
}

void vault_list(t_vault *vault){
    size_t i = 0;

    while (i < vault->count){
        printf("%d. %s (%s)\n", (int)i, vault->entries[i].name, vault->entries[i].user);
        i++;
    }
}

t_entry *vault_get(t_vault *vault, const char *name){
    size_t i = 0;
    while (i  < vault->count){
        if(strcmp(name, vault->entries[i].name) == 0)
            return &vault->entries[i];
        i++;
    }
    return NULL;
}

int vault_save(t_vault *vault, const char *filename){
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if(fd < 0)
        return -1;

    ssize_t n = write(fd, &vault->count, sizeof(size_t));
    if (n != sizeof(size_t)) {
        close(fd);
        return -1;
    }

    n = write(fd, vault->entries, vault->count * sizeof(t_entry));
    if (n != (ssize_t)(vault->count * sizeof(t_entry))) {
        close(fd);
        return -1;
    }

    close(fd);

    return 0;
}

int vault_load(t_vault *vault, const char *filename){
    int fd = open(filename, O_RDONLY, 0);

    if (fd < 0)
        return -1;

    size_t count;
    ssize_t n = read(fd, &count, sizeof(size_t));
    if (n != sizeof(size_t)) {
        close(fd);
        return -1;
    }

    if (count > vault->capacity){
        t_entry *tmp = realloc(vault->entries, count * sizeof(t_entry));
        if (tmp == NULL){
            close(fd);
            return -1;

        }
        vault->entries=tmp;
        vault->capacity=count;
    }
    
    n = read(fd, vault->entries, count * sizeof(t_entry));
    if (n != (ssize_t)(count * sizeof(t_entry))) {
        close(fd);
        return -1;
    }

    vault->count=count;

    close(fd);
    return 0;
}

void vault_free(t_vault *vault){
    t_vault *v = vault;
    if (vault->entries == NULL)
        return;
    free(vault->entries);
    vault->count=0;
    vault->capacity=0;
}