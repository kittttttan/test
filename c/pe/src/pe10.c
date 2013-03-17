/*
 * pe10.c
 * http://kittttttan.web.fc2.com/c/pe10
 */
#include <pe10.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifdef _WIN32
#define UINT64 "I64u"
#else
#define UINT64 "llu"
#endif

void pe10(uint32_t n) {
  int *s;
  uint32_t i, j, sq;
  uint64_t sum = 0;

  assert(n > 0);
  s = (int*)malloc(sizeof(int) * n);
  if (!s) {
    fprintf(stderr, "%s:%d: failed malloc.\n", __FILE__, __LINE__);
    return;
  }

  s[0] = 0;
  s[1] = 0;
  for (i = 2; i <= n; ++i) {
    s[i] = 1;
  }

  sq = (uint32_t)sqrt(n);
  for (i = 2; i < sq + 1; i++) {
    if (s[i]) {
      for (j = i * i; j <= n; j += i) {
        s[j] = 0;
      }
    }
  }

  for (i = 0; i <= n; i++) {
    if (s[i]) {
      sum += i;
    }
  }
  free(s);

  printf("%" UINT64 " below %u\n", sum, n);
}

int pe10_main(void) {
  uint32_t n;

  while (1) {
    printf("below: ");
    if (scanf("%u", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe10(n);
    }
  }

  return 0;
}
