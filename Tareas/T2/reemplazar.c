#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

//Leonardo Rikhardsson

char *reemplazo(char *s, char c, char *pal) {
    char* temp = s;
    int cnt = 0;
    int pallen = strlen(pal);
    while (*temp) {
        if (*temp == c) {
            cnt += pallen;
        }
        else {
            cnt++;
        }
        temp++;
    }
    char* tot = (char*)malloc(cnt + 1); 
    char* k = tot;
    temp = s;
    while (*temp) {
        if (*temp == c) {
            strcpy(k, pal);
            k += pallen;
            temp++;
        } 
        else {
            *k = *temp;
            k++;
            temp++;  
        }
    }
    *k = '\0';
    return tot;
}

void reemplazar(char *s, char c, char *pal) {
    int slen = strlen(s);
    int pallen = strlen(pal);
    int cnt = 0;
    char* i;
    char* j;
    char* temp = s;
    while (*temp) {
        if (*temp == c) {
            cnt++;
        }
        temp++;
    }
    int res = slen + cnt * (pallen - 1);
    if (pallen == 0) {
        i = s;
        j = s;
        while (*i) {
            if (*i == c) {
            } 
            else {
                *j = *i;
                j++;
            }
            i++;
        }
        *j = '\0';
    } 
    else if (pallen == 1) {
        i = s;
        j = s;
        while (*i) {
            if (*i == c) {
                *j = *pal;
                j++;
            }
            else {
                *j = *i;
                j++;
            }
            i++;
        }
        *j = '\0';
    }        
    else {
        i = s + slen;
        j = s + res;
        char* pal2 = pal + pallen - 1;
        while (s <= i) {
            if (*i == c) {
                pal2 = pal + pallen - 1;
                while (pal2>=pal) {
                    *j = *pal2;
                    j--;
                    pal2--;
                }
            } 
            else {
                *j = *i;
                j--;
            }
            i--;
        }
    }
}
