# XTEA simplement

## 1. Creer `src/libc/xtea.c`

```c
#include "libc.h"

typedef unsigned int u32;

void xtea(void *data, size_t size, const char *password, int decrypt)
{
    u32 key[4] = {0, 0, 0, 0};
    u32 *block = (u32 *)data;
    u32 left;
    u32 right;
    u32 sum;
    u32 delta = 0x9E3779B9;
    size_t i = 0;
    size_t p = 0;
    int round;

    while (password[p]) {
        key[p % 4] = key[p % 4] * 33 ^ (unsigned char)password[p];
        p++;
    }
    while (i + 1 < size / 4) {
        left = block[i];
        right = block[i + 1];
        sum = decrypt ? 0xC6EF3720 : 0;
        round = 0;
        while (round < 32) {
            if (decrypt) {
                right -= (((left << 4) ^ (left >> 5)) + left)
                    ^ (sum + key[(sum >> 11) & 3]);
                sum -= delta;
                left -= (((right << 4) ^ (right >> 5)) + right)
                    ^ (sum + key[sum & 3]);
            } else {
                left += (((right << 4) ^ (right >> 5)) + right)
                    ^ (sum + key[sum & 3]);
                sum += delta;
                right += (((left << 4) ^ (left >> 5)) + left)
                    ^ (sum + key[(sum >> 11) & 3]);
            }
            round++;
        }
        block[i] = left;
        block[i + 1] = right;
        i += 2;
    }
}
```

Cette fonction coupe la base en blocs de 8 octets. Elle melange chaque bloc
32 fois avec une cle fabriquee depuis le mot de passe principal.

## 2. Modifier `include/libc/libc.h`

Ajouter cette ligne juste avant `#endif` :

```c
void xtea(void *data, size_t size, const char *password, int decrypt);
```

## 3. Sauvegarder la base

Faire une copie de la base, chiffrer la copie, puis l'ecrire :

```c
database_t copy;

memcpy(&copy, &database, sizeof(database_t));
xtea(&copy, sizeof(database_t), master_password, 0);
write(fd, &copy, sizeof(database_t));
```

`0` signifie **chiffrer**.

## 4. Charger la base

Lire la base, puis la dechiffrer :

```c
read(fd, &database, sizeof(database_t));
xtea(&database, sizeof(database_t), master_password, 1);
```

`1` signifie **dechiffrer**.

## A retenir

La taille de `database_t` doit etre un multiple de 8, car XTEA travaille bloc
par bloc. Un mot de passe faible peut toujours etre teste par force brute :
XTEA ne remplace pas un bon mot de passe principal.

Pour compiler :

```sh
make re
```

Le Makefile ajoutera automatiquement `xtea.c` parce que son extension est `.c`.
