/*
 * pe9.c
 * http://kittttttan.web.fc2.com/c/pe9
 */
#include <pe9.h>
#include <stdio.h>

void pe9(int n) {
  int l, x, y, z;

  l = (n >> 1) + 1;
  for (x = 1; x < l; ++x) {
    for (y = x; y < l; ++y) {
      z = n - x - y;
      if (x * x + y * y == z * z) {
        printf("%d (n = %d)\n", x * y * z, n);
        return;
      }
    }
  }

  printf("Not Found (n = %d)\n", n);
}

int pe9_main(void) {
  int n;

  while (1) {
    printf("x + y + z = ");
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe9(n);
    }
  }

  return 0;
}
