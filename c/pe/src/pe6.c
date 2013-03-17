/*
 * pe6.c
 * http://kittttttan.web.fc2.com/c/pe6
 */
#include <pe6.h>

#include <stdio.h>

void pe6(int n) {
  printf("%d (n = %d)\n",
         n * (n + 1) * (n - 1) * (3 * n + 2) / 12,
         n);
}

int pe6_main(void) {
  int n;

  while (1) {
    puts("n: ");
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe6(n);
    }
  }

  return 0;
}
