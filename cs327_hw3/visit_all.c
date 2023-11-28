#include <stdio.h>

#define SIDE 401

int main(int argc, char *argv[])
{
  int i;
  int j;

  for (i = 0; i < SIDE; i++) {
    for (j = 0; j <= i && j < (SIDE - 1); j++) {
      if (i & 1) { /* odd  */
        putchar('s');
      } else {     /* even */
        putchar('n');
      }
    }
    for (j = 0; j <= i && i < (SIDE - 1); j++) {
      if (i & 1) { /* odd  */
        putchar('e');
      } else {     /* even */
        putchar('w');
      }
    }
    putchar('\n');
  }
  putchar('f');
  putchar('0');
  putchar(' ');
  putchar('0');
  putchar('q');
  putchar('\n');
  
  return 0;
}
