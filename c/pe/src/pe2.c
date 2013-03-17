/*
 * pe2.c
 * http://kittttttan.web.fc2.com/c/pe2
 */
#include <pe2.h>

#include <stdio.h>
#include <stdint.h>

#ifdef _WIN32
#define UINT64 "I64u"
#else
#define UINT64 "llu"
#endif

void pe2(uint64_t n) {
  uint64_t a, b, t, sum;

  a = b = 1;
  sum = 0;
  while (a < n) {
    if ((a & 1) == 0) {
      sum += a;
    }
    t = a;
    a += b;
    b = t;
  }

  printf("%" UINT64 " below %" UINT64 "\n", sum, n);
}

int pe2_main(void) {
  uint64_t n;

  while (1) {
    printf("below: ");
    if (scanf("%" UINT64, &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe2(n);
    }
  }

  return 0;
}
