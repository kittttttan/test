/*
 * pe20.c
 * http://kittttttan.web.fc2.com/c/pe20
 */
#include <pe20.h>

#include <stdio.h>
#include <string.h>

enum { MAX_ORDER = 256 };

void pe20(int n) {
  static int bits[MAX_ORDER];
  int i;
  int j;
  int sum = 0;
  
  /* init: set 0...01 */
  memset(bits, 0, sizeof(int) * MAX_ORDER);
  bits[0] = 1;

  if (n > 1) {
    for (j = 2; j <= n; ++j) {
      /* multiply */
      for (i = 0; i < MAX_ORDER; ++i) {
        bits[i] *= j;
      }
      
      /* ceil */
      for (i = 0; i < MAX_ORDER - 1; ++i) {
        bits[i + 1] += bits[i] / 10000;
        bits[i] %= 10000;
      }

      /* check overflow */
      if (bits[MAX_ORDER - 1] > 9999) {
        fprintf(stderr, "overflow\n");
        return;
      }
    }
  }
  
  i = MAX_ORDER;
  /* ignore following zeros */
  while (i--) {
    if (bits[i]) break;
  }

  /* print for debug */
  printf("%d! = ", n);
  printf("%d", bits[i]);
  do {
    sum += bits[i] % 10;
  } while (bits[i] /= 10);
  if (i > 0) {
    while (i--) {
      printf("%04d", bits[i]);
      
      do {
        sum += bits[i] % 10;
      } while (bits[i] /= 10);
    }
  }
  printf("\n");
  
  printf("sum of digits = %d\n", sum);
}

int pe20_main(void) {
  int n;

  while (1) {
    printf("n!: ");
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe20(n);
    }
  }

  return 0;
}
