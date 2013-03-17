/*
 * pe14.c - Which starting number produces the longest Collatz chain?
 * http://kittttttan.web.fc2.com/c/pe14
 */
#include <pe14.h>

#include <stdio.h>

unsigned long count(unsigned long n) {
  unsigned long c;

  c = 1;
  while (n > 1) {
    if (n & 1) {
      n = 3 * n + 1;
    } else {
      n >>= 1;
    }
    ++c;
  }

  return c;
}

void pe14(unsigned long begin, unsigned long limit) {
  unsigned long m, mi, i, c;

  m = mi = 0;
  if ((begin & 1) == 0) {
    c = count(begin);
    if (m < c) {
      m = c;
      mi = begin;
    }
    ++begin;
  }

  for (i = begin; i < limit; i += 2) {
    c = count(i);
    if (m < c) {
      m = c;
      mi = i;
    }
  }

  printf("%lu produces %lu Collatz chain\n", mi, m);
}

int pe14_main(void) {
  pe14(500001, 1000000);

  return 0;
}
