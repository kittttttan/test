/*
 * pe12.c
 * http://kittttttan.web.fc2.com/c/pe12
 */

/* http://kittttttan.web.fc2.com/c/divs */
#include <pe12.h>
#include <divs.h>

#include <stdio.h>
#include <math.h>

void pe12(unsigned long n) {
  unsigned long i, c, t;

  t = 1;
  i = 2;
  while ((c = cnt_divs(t)) < n) {
    t += i++;
  }

  printf("%lu\n", t);
}

int pe12_main(void) {
  unsigned long n;

  while (1) {
    printf("below: ");
    if (scanf("%lu", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe12(n);
    }
  }

  return 0;
}
