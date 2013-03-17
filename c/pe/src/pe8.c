/*
 * pe8.c
 * http://kittttttan.web.fc2.com/c/pe8
 */
#include <pe8.h>

#include <stdio.h>

enum { DIGITS_LENGTH = 1000 };

void pe8(int n) {
  /* http://kittttttan.web.fc2.com/c/pe8.txt */
  static const char* FILENAME = "pe8.txt";
  int digits[DIGITS_LENGTH];

  int c, m, t, i, j;
  FILE *fp;

  fp = fopen(FILENAME, "r");
  if (!fp) {
    fprintf(stderr, "%s:%d: Can't open %s\n", __FILE__, __LINE__, FILENAME);
    return;
  }

  i = 0;
  while ((c = getc(fp)) != EOF) {
    if (c >= '0' && c <= '9') {
      if (i >= DIGITS_LENGTH) {
        fprintf(stderr, "%s:%d: too many numbers.\n", __FILE__, __LINE__);
        break;
      }
      digits[i++] = c - '0';
    }
  }

  if (ferror(fp)) {
    fprintf(stderr, "file error.");
    clearerr(fp);
  }
  fclose(fp);

  m = 0;
  if (n > 0 && n < 1000) {
    for (i = 0; i < 1000 - n; ++i) {
      t = 1;
      for (j = 0; j < n; ++j) {
        t *= digits[i + j];
      }
      if (m < t) {
        m = t;
      }
    }
  }

  printf("%d (n = %d)\n", m, n);
}

int pe8_main(void) {
  int n;

  while (1) {
    printf("digits: ");
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe8(n);
    }
  }

  return 0;
}
