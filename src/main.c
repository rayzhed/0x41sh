#include "libc.h"
#include "vault.h"



static int read_line(const char *prompt, char *dest, size_t max, char *buffer, size_t bufsize){
  printf("%s", prompt);

  ssize_t r = getline(&buffer, &bufsize, 0);
  if (r <= 0)
    return -1;
  
  if (buffer[r - 1] == '\n')
    buffer[r - 1] = '\0';
  
  strncpy(dest, buffer, max - 1);
  return 0;
  
}

int main(int argc, char **argv, char **envp)
{
  (void)argc; (void)argv; (void)envp;

  size_t size = 1024;
  char *buffer = malloc(size);
  if (buffer == NULL)
    return 1;
  ssize_t reader = 0;

   /*
  _  __          _____                   _____          
 | |/ /         |  __ \                 |  __ \         
 | ' / ___ _   _| |__) |_ _ ___ ___  ___| |__) |_ _ ___ 
 |  < / _ \ | | |  ___/ _` / __/ __|/ _ \  ___/ _` / __|
 | . \  __/ |_| | |  | (_| \__ \__ \  __/ |  | (_| \__ \
 |_|\_\___|\__, |_|   \__,_|___/___/\___|_|   \__,_|___/
            __/ |                                       
           |___/                                        */
  printf("  _  __          _____                   _____          \n | |/ /         |  __ \\                 |  __ \\         \n | ' / ___ _   _| |__) |_ _ ___ ___  ___| |__) |_ _ ___ \n |  < / _ \\ | | |  ___/ _` / __/ __|/ _ \\  ___/ _` / __|\n | . \\  __/ |_| | |  | (_| \\__ \\__ \\  __/ |  | (_| \\__ \\\n |_|\\_\\___|\\__, |_|   \\__,_|___/___/\\___|_|   \\__,_|___/\n            __/ |                                       \n           |___/                                        v1.1\n\n\n\n\n");
  char master[64];

  printf("(n'essaye pas de brute-force sinon je vais le dire aux adultes)\nMaster password: ");
  reader = getline(&buffer, &size, 0);
  if (reader > 0 && buffer[reader - 1] == '\n')
    buffer[reader - 1] = '\0';
  strncpy(master, buffer, 63);
  t_vault v;
  if (vault_init(&v) < 0) { printf("Oups, on dirait bien que ton vault à crash, bye..."); exit(-1); }

  int r = vault_load(&v, "vault.db", master);
  if (r == -2) {
      printf("zoubin/sh il veut pas :{\n");
      exit(1);
  }
  if (r == -1) {
      printf("ton vault.db est tout casse, je prefere pas l'ouvrir sinon je vais ecraser ce qui reste dedans :{\n");
      exit(1);
  }
  if (r == -3) {
      char verif[64];

      if (read_line("c'est ton premier zoubicoffre, retape ton mot de passe pour etre sur: ", verif, 64, buffer, size) < 0
      || strcmp(master, verif) != 0) {
          printf("c'est pas le meme, on recommence, jvais pas t'enfermer dehors :{\n");
          exit(1);
      }
  }
  
  while (1){

    printf("zoubin/sh> ");
    reader = getline(&buffer, &size, 0);

    if (reader <= 0){
      printf("je met tout dans mon sac bye bye !");
      if (vault_save(&v, "vault.db", master) < 0)
        printf("ouuups j'ai fait tomber le sac.. tes zoubicreds sont perdus :((\n");
      vault_free(&v);
      exit(0);
    }

    if (buffer[reader - 1] == '\n')
      buffer[reader - 1] = '\0';

    if (strcmp(buffer, "exit") == 0){
      printf("je met tout dans mon sac bye bye !");
      if (vault_save(&v, "vault.db", master) < 0)
        printf("ouuups j'ai fait tomber le sac.. tes zoubicreds sont perdus :((\n");
      vault_free(&v);
      exit(0);
    }else if (strcmp(buffer, "help") == 0) {
      printf("help - bah tu viens de faire la commande quoi\nsave - TRES IMPORTANT SI TU SAVE PAS J'OUBLIE TOUT ORH !1!1!\nget - dit moi quoi chercher et je te montre un de tes jolis zoubicreeeeeds\nadd - si tu veut me donner tes zoubicreds :}\ndel - si ta besoin que je supprime un de tes zoubicreds appel moi !\nlist - Pour afficher tout tes zoubicreds que je te cache au chaud hehe\ngen - si tu cherche un zoubicreds je peut t'inspirer !\necho <texte> - c'est un perroquet :}\nclear - salut je suis le nettoyeur mon boulot est de.. nettoyer ton.. terminal !\nexit - essaye pour voir ?\n");
    } else if (strncmp(buffer, "echo ", 5) == 0){
      printf("%s\n", buffer+5);
    } else if(strcmp(buffer, "clear") == 0) {
      printf("\033[2J");
    } else if (strcmp(buffer, "list") == 0) {
        vault_list(&v);
    } else if (strcmp(buffer, "save") == 0) {
        if (vault_save(&v, "vault.db", master) < 0)
            printf("erreur sauvegarde\n");
        else
            printf("vault sauvegarde\n");
    } else if (strcmp(buffer, "add") == 0) {
        char name[MAX_LEN];
        char user[MAX_LEN];
        char pass[MAX_LEN];

        if (read_line("donne moi le nom de ton service stpppp: ", name, MAX_LEN, buffer, size) < 0
        || read_line("t'es qui ??: ", user, MAX_LEN, buffer, size) < 0
        || read_line("un mot de passe peutetre eheh :}: ", pass, MAX_LEN, buffer, size) < 0) {
            printf("saisie annulee\n");
        } else {
            if (vault_add(&v, name, user, pass) < 0)
                printf("Oups j'ai tout zoublier..\n");
            else
                printf("et voili voilou, je vais cacher sa !\n");
        }
    } else if (strncmp(buffer, "del ", 4) == 0) {
        if (vault_del(&v, buffer + 4) < 0)
            printf("hum je trouve pas ce truc moi..\n");
        else
            printf("et pouf c'est jeter dans la laaaave sa bruuule !!\n");
    } else if (strncmp(buffer, "get ", 4) == 0) {
        t_entry *e = vault_get(&v, buffer+4);
        if (e == NULL)
          printf("je trouve pas ton nom, jpense tu l'a passer a un autre zoubimaaannnn\n");
        else
          printf("ton zoubiname c'est %s et ton zoubicreds c'est > %s < chuuuut faut pas dire que jte l'ai dit c'est un secret..\n", e->user, e->password);

    } else if (strcmp(buffer, "gen") == 0) {
      char pass[MAX_LEN];
      if (generate_password(pass, 20) < 0)
          printf("eh j'ai trouver.. oups on dirait que la feuille est.. vide ?\n");
      else
          printf("eh j'ai trouver une feuille par terre regarde : %s\n", pass);
    } else {
      printf("commande inconnue. stp fait un effort t'a toute les commandes dans help..\n");
    }

  }
 

  return 0;
}
