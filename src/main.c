#include "libc.h"
#include "vault.h"

int main(int argc, char **argv, char **envp)
{
  size_t size = 1024;
  char *buffer = malloc(size);
  if (buffer == NULL)
    return 1;
  ssize_t reader = 0;

  /*while (1){

    printf("zoubin/sh> ");
    reader = getline(&buffer, &size, 0);

    if (reader <= 0)
      exit(0);

    if (buffer[reader - 1] == '\n')
      buffer[reader - 1] = '\0';

    if (strcmp(buffer, "exit") == 0){
      exit(0);
    }else if (strcmp(buffer, "help") == 0) {
      printf("help - bah tu viens de faire la commande quoi\necho <texte> - c'est un perroquet :}\nexit - essaye pour voir ?\n");
    } else if (strncmp(buffer, "echo ", 5) == 0){
      printf("[%s] strncmp=%d\n", buffer, strncmp(buffer, "echo ", 5));
      printf("%s\n", buffer+5);
    } else if(strcmp(buffer, "clear") == 0) {
      printf("\033[2J");
    } else {
      printf("commande inconnue. stp fait un effort t'a toute les commandes dans help..\n");
    }

  }*/

  char *master = "amine";

  t_vault v;
  vault_init(&v);
  vault_add(&v, "github.com", "rayzhed", "pass1");
  vault_add(&v, "gmail.com", "moi", "pass2");
  vault_save(&v, "vault.db", master);
  puts("sauvegarde");

  t_vault v2;
  vault_init(&v2);
  if (vault_load(&v2, "vault.db", master) < 0) {
      puts("erreur chargement");
      return 1;
  }
  puts("charge :");
  vault_list(&v2);

  return 0;
}
