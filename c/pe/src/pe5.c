/*
 * pe5.c
 * http://kittttttan.web.fc2.com/c/pe5
 */
#include <pe5.h>

/* http://kittttttan.web.fc2.com/c/gcd */
#include <gcd.h>

#include <stdio.h>
#include <stdlib.h>

void pe5(unsigned long n) {
  unsigned long i, d = 1;

  for (i = 2; i <= n; ++i) {
    d = lcm(d, i);
  }

  printf("%lu below %lu\n", d, n);
}

int pe5_main(void) {
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
      pe5(n);
    }
  }

  return 0;
}
