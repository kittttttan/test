/*
 * pe13.c
 * http://kittttttan.web.fc2.com/c/pe13
 */
#include <pe13.h>

#include <stdio.h>

void pe13(void) {
  /* http://kittttttan.web.fc2.com/c/pe13.txt */
  static const char* FILENAME = "pe13.txt";

  int c, i, j, k, sum;
  int nums[5000], res[128];
  FILE* fp;

  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "%s:%d: Can't open %s\n", __FILE__, __LINE__, FILENAME);
    return;
  }

  i = 0;
  while ((c = getc(fp)) != EOF) {
    if (c >= '0' && c <= '9') {
      nums[i++] = c - '0';
    }
  }

  if (ferror(fp)) {
    fprintf(stderr, "file error.");
    clearerr(fp);
  }
  fclose(fp);

  sum = k = 0;
  for (i = 49; i >= 0; --i) {
    for (j = 0; j < 5000; j += 50) {
      sum += nums[i + j];
    }
    res[k++] = sum % 10;
    sum /= 10;
  }

  while (sum) {
    res[k++] = sum % 10;
    sum /= 10;
  }

  for (i = 0; i < 10; ++i) {
    putchar(res[--k] + '0');
  }
  putchar('\n');
}

int pe13_main(void) {
  pe13();

  return 0;
}
