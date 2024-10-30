#include <stdio.h>
#include <stdlib.h>

#include "elim-rango.h"

//Leonardo Rikhardsson

void eliminarRango(Nodo **phead, double y, double z) {
    Nodo *a = *phead;
    Nodo *b = NULL;
    //Sabemos que debemos recorrer una lista no vacia y sin pasarnos de z
    while (a != NULL && a->x <= z) {
        if (a->x >= y) {
          //Si el valor que viene antes es nulo, entonces avanzamos
            if (b == NULL) {
                *phead = a->prox;
                free(a);
                a = *phead;
            }
            else {
                b->prox = a->prox;
                free(a);
                a = b->prox;
            }
        }
        //Cuando el valor de la lista sea menor que y
        else {
            b = a;
            a = a->prox;
        }
    }
}
