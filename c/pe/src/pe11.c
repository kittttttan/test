/*
 * pe11.c
 * http://kittttttan.web.fc2.com/c/pe11
 */
#include <pe11.h>
#include <stdio.h>

void pe11(void) {
  /* http://kittttttan.web.fc2.com/c/pe11.txt */
  static const char* FILENAME = "pe11.txt";

  int i, j, k, n, c;
  unsigned long ud, lr, d0, d1, m;
  int nums[20][20];
  FILE* fp;

  fp = fopen(FILENAME, "r");
  if (!fp) {
    fprintf(stderr, "%s:%d: Can't open %s\n", __FILE__, __LINE__, FILENAME);
    return;
  }

  i = j = 0;
  n = -1;
  while ((c = getc(fp)) != EOF) {
    if (c >= '0' && c <= '9') {
      if (n == -1) {
        n = 10 * (c - '0');
      } else {
        n += c - '0';
        nums[i][j++] = n;
        n = -1;
        if (j > 19) {
          j = 0;
          ++i;
          if (i > 19) {
            break;
          }
        }
      }
    }
  }

  if (ferror(fp)) {
    fprintf(stderr, "file error.");
    clearerr(fp);
  }
  fclose(fp);

  m = 0;
  for (i = 0; i < 20; ++i) {
    for (j = 0; j < 20; ++j) {
      ud = lr = d0 = d1 = 1;
      for (k = 0; k < 4; ++k) {
        if (i < 16) {
          lr *= nums[i + k][j];
        } else {
          lr = 0;
        }
        if (j < 16) {
          ud *= nums[i][j + k];
        } else {
          ud = 0;
        }
        if (i < 16 && j < 16) {
          d0 *= nums[i + k][j + k];
          d1 *= nums[i + k][j + 4 - k];
        } else {
          d0 = d1 = 0;
        }
      }
      if (m < ud) {
        m = ud;
      }
      if (m < lr) {
        m = lr;
      }
      if (m < d0) {
        m = d0;
      }
      if (m < d1) {
        m = d1;
      }
    }
  }

  printf("%lu\n", m);
}

int pe11_main(void) {
  pe11();

  return 0;
}
