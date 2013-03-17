/*
 * pe21.c
 * http://kittttttan.web.fc2.com/c/pe21
 */
#include <pe21.h>

/* http://kittttttan.web.fc2.com/c/spd */
#include <spd.h>

#include <stdio.h>
#include <string.h>

static int debug_on = 0;

void pe21(int n) {
  int i;
  int t;
  int sum = 0;
  
  for (i = 2; i < n + 1; ++i) {
    t = spd(i);
    if (i < t && i == spd(t)) {
      if (debug_on) printf("(%d, %d)\n", i, t);
      sum += i + t;
    }
  }
  
  printf("%d\n", sum);
}

int pe21_main(void) {
  int n;

  while (1) {
    puts("below: ");
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe21(n);
    }
  }

  return 0;
}
