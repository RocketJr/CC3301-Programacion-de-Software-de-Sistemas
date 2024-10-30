#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

#define MAXTAM (800+2)

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <diccionario> <llave>\n", "./consultar.bin");
        return -1;
    }

    char *filename = argv[1];
    char *llave = argv[2];
    int tamLlave= strlen(llave);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror(filename);
        return -1;
    }

    // Tamaño archivo
    char first_line[MAXTAM];
    fgets(first_line, sizeof(first_line), file);
    int line_size = strlen(first_line);

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);

    if (line_size == 0 || first_line[line_size-1] != '\n') {
        fprintf(stderr, "%s: el dicionario esta vacio\n", filename);
        return -1;
    }

    // Verifica la consistencia del tamaño del archivo y linea
    if (file_size % line_size != 0) {
        fprintf(stderr, "%s: el tamaño del archivo no es multiplo del tamaño de la linea\n", filename);
        return -1;
    }
    
    // Numero de lineas
    int num_lines = file_size / line_size;
    int hash = hash_string(llave);
    int index = hash % num_lines;

    // Buscar la llave en el archivo
    while (1) {
        char line[MAXTAM];
        fseek(file, index * line_size, SEEK_SET);
        fgets(line, tamLlave + 1, file);

        if (strcmp(line, llave) == 0) {
            // Caso en que la llave sea encontrada, pero no presente ":"
            fseek(file, index * line_size + tamLlave, SEEK_SET);
            if (fgetc(file) != ':') {
                fprintf(stderr, "%s: linea %d no posee : para terminar la llave\n", filename, index);
                return -1;
            }
            else {
                // Caso en que se encuentre la llave, entonces imprima el valor
                fgets(line, sizeof(line), file);
                printf("%s\n", line);
                break;
            }
        } else if (strcmp(line, "\n") == 0) {
            // Caso en que no se encuentre la llave
            fprintf(stderr, "%s: el diccionario no contiene la llave %s\n", filename, llave);
            return -1;
        } else {
            // Se verifica ahora que las lineas tengan un tamaño correcto
            fseek(file, index * line_size, SEEK_SET);
            fgets(line, sizeof(line), file);
            if (strlen(line) != line_size) {
                fprintf(stderr, "%s: linea %d de tamaño incorrecto\n", filename, index);
                return -1;
            }
            index = (index + 1) % num_lines;
            if (index == hash % num_lines) {
                // Caso en que no se encuentre la llave
                fprintf(stderr, "%s: el diccionario no contiene la llave %s\n", filename, llave);
                return -1;
            }
        }
    }
    fclose(file);
    return 0;
}
