#include "libc.h"
#include "vault.h"

/*Vault iniiiiiiit*/
int vault_init(t_vault *vault){
    vault->entries = malloc(8 * sizeof(t_entry));
    if (vault->entries == NULL){
        return -1;
    }
    vault->count = 0;
    vault->capacity = 8;

    return 0;
}

/*Vault Helper*/
static void copy_field(char *dest, const char *src){
    size_t len = strlen(src);
    if (len >= MAX_LEN)
        len = MAX_LEN - 1;
    memcpy(dest, src, len);
    dest[len] = '\0';
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

    while (i < vault->count){
        if (strcmp(name, vault->entries[i].name) == 0)
            return &vault->entries[i];

        i++;
    }

    return NULL;
}

int vault_save(t_vault *vault, const char *filename, const char *master) {
    /*on ecrit a cote, on remplace l'ancien coffre qu'une fois tout ecrit*/
    char tmp[128];
    size_t len = strlen(filename);

    if (len > sizeof(tmp) - 5)
        return -1;

    memcpy(tmp, filename, len);
    memcpy(tmp + len, ".tmp", 5);

    int fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if (fd < 0)
        return -1;

    ssize_t n = write(fd, &vault->count, sizeof(size_t));

    if (n != sizeof(size_t)) {
        close(fd);
        return -1;
    }

    size_t size = vault->count * sizeof(t_entry);
    size_t total = sizeof(unsigned long long) + size;
    unsigned char *copy = malloc(total);

    if (copy == NULL) {
        close(fd);
        return -1;
    }

    /*le canari passe devant, comme ça il est chiffré avec le reste*/
    unsigned long long canary = CANARY;

    memcpy(copy, &canary, sizeof(canary));
    memcpy(copy + sizeof(canary), vault->entries, size);

    xtea(copy, total, master, 0);

    n = write(fd, copy, total);

    free(copy);

    if (n != (ssize_t)total) {
        close(fd);
        return -1;
    }

    close(fd);

    if (rename(tmp, filename) < 0)
        return -1;

    return 0;
}

int vault_load(t_vault *vault, const char *filename, const char *master) {
    int fd = open(filename, O_RDONLY, 0);

    /*-3 = y'a pas de fichier (1er lancement), -1 = y'en a un mais il est casse*/
    if (fd < 0)
        return -3;

    size_t count;

    ssize_t n = read(fd, &count, sizeof(size_t));

    if (n != sizeof(size_t)) {
        close(fd);
        return -1;
    }

    /*count sort du fichier, on lui fait pas confiance*/
    if (count > 100000) {
        close(fd);
        return -1;
    }

    size_t size = count * sizeof(t_entry);
    size_t total = sizeof(unsigned long long) + size;
    unsigned char *buf = malloc(total);

    if (buf == NULL) {
        close(fd);
        return -1;
    }

    n = read(fd, buf, total);

    if (n != (ssize_t)total) {
        free(buf);
        close(fd);
        return -1;
    }

    xtea(buf, total, master, 1);

    /*canari cassé = mauvais master :{*/
    unsigned long long canary;

    memcpy(&canary, buf, sizeof(canary));

    if (canary != CANARY) {
        free(buf);
        close(fd);
        return -2;
    }

    if (count > vault->capacity){
        t_entry *tmp = realloc(vault->entries, size);

        if (tmp == NULL){
            free(buf);
            close(fd);
            return -1;
        }

        vault->entries = tmp;
        vault->capacity = count;
    }

    memcpy(vault->entries, buf + sizeof(canary), size);

    vault->count = count;

    /*le buffer est plein de mots de passe en clair, on le nettoie avant de le rendre*/
    size_t z = 0;

    while (z < total)
        buf[z++] = 0;

    free(buf);

    close(fd);

    return 0;
}

void vault_free(t_vault *vault){
    if (vault->entries == NULL)
        return;
    free(vault->entries);
    vault->entries=NULL;
    vault->count=0;
    vault->capacity=0;
}

int vault_del(t_vault *vault, const char *name){
    size_t i = 0;
    size_t j = 0;

    while (i < vault->count){
        if (strcmp(name, vault->entries[i].name) == 0) {
            j = i;
            while (j < vault->count - 1) {
                vault->entries[j] = vault->entries[j + 1];
                j++;
            }
            vault->count--;
            return 0;
        }
        i++;
    }

    return -1;
}