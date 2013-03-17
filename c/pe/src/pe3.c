/*
 * pe3.c
 * http://kittttttan.web.fc2.com/c/pe3
 */
#include <pe3.h>

/* http://kittttttan.web.fc2.com/c/divs */
#include <divs.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

enum { MAX_DIVS_CNT = 128 };

void pe3(unsigned long n) {
  unsigned long p[MAX_DIVS_CNT];
  size_t len;

  len = get_divs(p, n);
  if (len) {
    printf("Max prime factor of %lu is %lu\n", n, p[len - 1]);
  } else {
    printf("%lu has no prime factors\n", n);
  }
}

int pe3_main(void) {
  unsigned long n;

  while (1) {
    printf("Max prime factor of: ");
    if (scanf("%lu", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe3(n);
    }
  }

  return 0;
}
