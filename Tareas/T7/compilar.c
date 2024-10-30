#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "pss.h"

// Leonardo Rikhardsson

// ... agregue aca las funciones y variables globales adicionales que necesite

Queue *TestQueue;

int cmpNom(void *ptr, int i, int j) {
    char **strings = ptr;
    char *s1 = strings[i];
    char *s2 = strings[j];

    char c1;
    char c2;

    for (;;) {
      c1= *s1;
      c2= *s2;

      if (c1==0)
        break;

      if (c1!=c2)
        break;

      s1++;
      s2++;
    }

    return c1 - c2;
}

void listDir(char *nom) {
  struct stat st_nom;
  int rc1;
  rc1= stat(nom, &st_nom);

  if (rc1!=0) {
    printf("%s no existe\n", nom);
    exit(0);
  }
  if (S_ISREG(st_nom.st_mode)) {
    // Es un archivo regular
    if (nom[strlen(nom) - 2] == '.' && nom[strlen(nom) - 1] == 'c') {
      char *nom2 = malloc(strlen(nom) + 2);
      strcpy(nom2, nom);
      nom2[strlen(nom) - 1] = 'o';
      
      struct stat st_test;
      int rc2;
      rc2 = stat(nom2, &st_test);
      
      if (rc2!=0 || st_nom.st_mtime > st_test.st_mtime) {
        char *CopiaNom = strdup(nom);
        put(TestQueue, CopiaNom);
      }
      free(nom2);
    }
  }
  else if (S_ISDIR(st_nom.st_mode)) {
    // Es un directorio
    DIR *dir = opendir(nom);
    if (dir == NULL) {
      perror(nom);
      exit(1);
    }
    for (struct dirent *entry = readdir(dir);
         entry != NULL;
         entry = readdir(dir)) {
      if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
        continue;
      }
      char *nom_arch= malloc(strlen(nom)+strlen(entry->d_name)+2);
      strcpy(nom_arch, nom);
      strcat(nom_arch, "/");
      strcat(nom_arch, entry->d_name);
      listDir(nom_arch);
      free(nom_arch);
    }
    closedir(dir);
  }
  else {
    // Podria ser un dispositivo, un link simbolico, etc.
    fprintf(stderr, "Archivo %s es de tipo desconocido\n", nom);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  if (argc!=2) {
    fprintf(stderr, "uso: %s <arch|dir>\n", argv[0]);
    exit(1);
  }
  
  // Inicio del queue
  TestQueue = makeQueue();
  
  listDir(argv[1]);
  
  int lenQueue = queueLength(TestQueue);
  
  char **Lista;
  Lista = malloc(lenQueue * sizeof(char *));
  
  for (int i = 0; i < lenQueue; i++) {
    Lista[i] = get(TestQueue);
  }
  
  sortPtrArray(Lista, 0, lenQueue - 1, cmpNom);
  
  for (int i = 0; i < lenQueue; i++) {
    printf("%s\n", Lista[i]);
    free(Lista[i]);
  }
  
  free(Lista);
  
  destroyQueue(TestQueue);
  
  return 0;
}
