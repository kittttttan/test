/*
 * pe15.c
 * http://kittttttan.web.fc2.com/c/pe15
 */
#include <pe15.h>

/* http://kittttttan.web.fc2.com/c/divs */
#include <divs.h>

#include <stdio.h>
#include <stdint.h>

#ifdef _WIN32
#define UINT64 "I64u"
#else
#define UINT64 "llu"
#endif

typedef struct _DivsData {
  int len;
  unsigned long divs[32];
} DivsData;

enum {
  MAX_M = 64,
  MAX_N = 64
};

/*
 *  (m + n)! / (m! * n!)
 */
void pe15(int m, int n) {
  int ps[MAX_M];
  DivsData dd[MAX_N];
  int i, j, k;
  uint64_t a;

  if (m > MAX_M || n > MAX_N) {
    printf("Too Large: max numbers are (%d, %d).\n", MAX_M, MAX_N);
    return;
  }
  if (m < n) {
    i = m; m = n; n = i;
  }

  for (i = 0; i < m; i++) {
    ps[i] = i + n + 1;
  }

  for (i = 0; i < n - 1; i++) {
    dd[i].len = get_divs(dd[i].divs, (unsigned long)i + 2);
  }

  for (i = 0; i < m; ++i) {
    for (j = 0; j < n - 1; ++j) {
      for (k = 0; k < dd[j].len; ++k) {
        if (dd[j].divs[k] > 1 && ps[i] % dd[j].divs[k] == 0) {
          ps[i] /= dd[j].divs[k];
          dd[j].divs[k] = 0;
          if (ps[i] < 2) {
            goto nextps;
          }
        }
      }
    }
nextps:
; // dummy to avoid compile error
  }

  a = 1;
  for (i = 0; i < m; i++) {
    if (ps[i] > 1) {
      a *= ps[i];
    }
  }

  printf("(%d + %d)! / (%d! * %d!) = %" UINT64 "\n",
          m, n, m, n, a);
}

int pe15_main(void) {
  int m, n;

  while (1) {
    printf("m n: ");
    if (scanf("%d %d", &m, &n) != 2) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!m && !n) {
        break;
      }
      pe15(m, n);
    }
  }

  return 0;
}
