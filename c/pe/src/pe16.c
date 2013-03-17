/*
 * pe16.c
 * http://kittttttan.web.fc2.com/c/pe16
 */
#include <pe16.h>

#include <stdio.h>
#include <string.h>

enum { MAX_ORDER = 128 };

/**
 * sum of digits for 2^n
 * @param[in] n power of 2
 */
void pe16(int n) {
  static int bits[MAX_ORDER];
  int i;
  int m = n;
  int sum = 0;
  
  /* init: set 0...01 */
  memset(bits, 0, sizeof(int) * MAX_ORDER);
  bits[0] = 1;

  if (n > 0) {
    while (m--) {
      /* x2 */
      for (i = 0; i < MAX_ORDER; ++i) {
        bits[i] <<= 1;
      }
      
      /* ceil */
      for (i = 0; i < MAX_ORDER - 1; ++i) {
        while (bits[i] > 9999) {
          ++bits[i + 1];
          bits[i] -= 10000;
        }
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
  printf("2 ^ %d = ", n);
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

int pe16_main(void) {
  int n;

  while (1) {
    puts("2^n: ");
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe16(n);
    }
  }

  return 0;
}
