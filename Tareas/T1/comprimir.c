#include <stdlib.h>
#include <string.h>

#include "comprimir.h"

//Leonardo Rikhardsson
uint comprimir(uint a[], int nbits) {
    uint rescomp = 0;
    int arreglo = 0;
    //Sacado del Aux grabado y hint del profesor
    unsigned m = -1;
    unsigned mask1 = (m<<(nbits-1));
    unsigned mask2 = ~(mask1 << 1);
    //Sacado de enunciado y Aux
    for(uint i=nbits;i <= sizeof(uint)<<3;i += nbits){
        rescomp <<= nbits-1;
        rescomp <<= 1;
        rescomp |= a[arreglo] & mask2;
        arreglo++;
    }
    return rescomp;
}
