/*
 * pe1.c
 * http://kittttttan.web.fc2.com/c/pe1
 */
#include <pe1.h>

#include <stdio.h>

#ifdef _WIN32
#define UINT64 "I64u"
#else
#define UINT64 "llu"
#endif

void pe1(uint64_t n) {
  uint64_t n3, n5, n15, sum = 0;

  if (n > 2) {
    n3 = (n - 1) / 3;
    n5 = (n - 1) / 5;
    n15 = (n - 1) / 15;
    sum = (3 * n3 * (n3 + 1) + 5 * n5 * (n5 + 1)
        - 15 * n15 * (n15 + 1)) >> 1;
  }

  printf("%" UINT64 " below %" UINT64 "\n", sum, n);
}

void pe1_loop(uint64_t n) {
  uint64_t i, sum = 0;
  if (n > 2) {
    for (i = 3; i < n; ++i) {
      if (i % 3 == 0 || i % 5 == 0) {
        sum += i;
      }
    }
  }

  printf("%" UINT64 " below %" UINT64 "\n", sum, n);
}

int pe1_main(void) {
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
      pe1(n);
    }
  }

  return 0;
}
