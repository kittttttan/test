/*
 * pe18.c
 * http://kittttttan.web.fc2.com/c/pe18
 */
#include <pe12.h>

#include <stdio.h>
#include <stdlib.h>

/* http://kittttttan.web.fc2.com/c/pe18.txt */
char DEFAULT_FILE_NAME[] = "pe18.txt";

#ifndef MAX
#define MAX(a,b) ((a)<(b)?(b):(a))
#endif

void pe18(char* filepath) {
  static const int SIZE = 15;

  FILE* fp;
  int c;
  int i, j;
  int t;
  int x, y;
  int** s;
  int invalid = 0;
  
  fp = fopen(filepath, "r");
  if (!fp) {
    fprintf(stderr, "failed to open %s\n", filepath);
    return;
  }
  
  // init array
  s = (int**)malloc(sizeof(int*) * SIZE);
  for (i = 0; i < SIZE; ++i) {
    s[i] = (int*)malloc(sizeof(int) * (i + 1));
  }
  
  x = y = 0;
  t = 0;
  
  // parse
  while ((c = getc(fp)) != EOF) {
    if (c >= '0' && c <= '9') {
      t = 10 * t + c - '0';
    } else if (c == '\n') {
      s[y][x] = t;
      printf("%02d\n", t);
      t = 0;
      ++y;
      x = 0;
      if (y >= SIZE) {
        invalid = 1;
        break;
      }
    } else {
      s[y][x] = t;
      printf("%02d ", t);
      t = 0;
      ++x;
      if (x >= SIZE) {
        invalid = 1;
        break;
      }
    }
  }
  
  if (invalid) {
    fprintf(stderr, "invalid file\n");
    fclose(fp);
  } else {
    s[y][x] = t;
    printf("%02d\n", t);
  
    if (ferror(fp)) {
      fprintf(stderr, "file error.");
      clearerr(fp);
    }
    fclose(fp);
    
    // sum
    for (i = 0; i < SIZE - 1; ++i) {
      for (j = 0; j < SIZE - i - 1; ++j) {
        s[SIZE - 1 - i - 1][j] +=
            MAX(s[SIZE - 1 - i][j], s[SIZE - 1 - i][j + 1]);
      }
    }
    printf("max sum = %d\n", s[0][0]);
  }
  
  // free array
  for (i = 0; i < SIZE; ++i) {
    free(s[i]);
  }
  free(s);
}

int pe18_main(void) {
  pe18(DEFAULT_FILE_NAME);

  return 0;
}
