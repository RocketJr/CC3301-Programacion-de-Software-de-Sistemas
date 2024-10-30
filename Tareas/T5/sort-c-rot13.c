#include <string.h>
//Leonardo Rikhardsson

int strCmp(char *s1, char *s2) {
    char c1;
    char c2;

    for (;;) {
      c1 = *s1;
      c2 = *s2;

      if (c1 == 0)
        break;

      // Aplicar ROT13
      if ('a'<= c1) {
        if (c1 <= 'm')
          c1 += 13;
        else if (c1 <='z')
          c1 -= 13;
      }
          
      if ('a'<= c2) {
        if (c2 <= 'm')
          c2 += 13;
        else if (c2 <='z')
          c2 -= 13;
      }

      if (c1 != c2)
        break;

      s1++;
      s2++;
    }
    return c1 - c2;
}

void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {
    // No modifique nada arriba de esta linea
    // Inicio de la parte que debe cambiar


    int t1= strCmp(p[0], p[1]);
    

    // Fin de la parte que debe cambiar
    // No Cambie nada mas a partir de aca
    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}
