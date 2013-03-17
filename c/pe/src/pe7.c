/*
 * pe7.c
 * http://kittttttan.web.fc2.com/c/pe7
 */
#include <pe7.h>

/* http://kittttttan.web.fc2.com/c/prime */
#include <prime.h>

#include <stdio.h>
#include <stdlib.h>

int pe7(int n) {
  int *ps;

  if (n < 1) {
    return 0;
  }

  ps = (int*)malloc(sizeof(int) * n);
  if (!ps) {
    fprintf(stderr, "%s:%d: failed malloc\n", __FILE__, __LINE__);
    return 0;
  }

  if (sieve(ps, n)) {
    printf("%dth prime is %d\n", n, ps[n - 1]);
  }
  free(ps);

  return 1;
}

int pe7_main(void) {
  int n;
  
  while (1) {
    printf("prime index of: ");
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe7(n);
    }
  }

  return 0;
}
