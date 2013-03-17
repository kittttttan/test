/*
 * pe17.c
 * http://kittttttan.web.fc2.com/c/pe17
 */
#include <pe17.h>

#include <stdio.h>

static int to20[] = {
  0, //
  3, //one
  3, //two
  5, //three
  4, //four
  4, //five
  3, //six
  5, //seven
  5, //eight
  4, //nine
  3, //ten
  6, //eleven
  6, //twelve
  8, //thirteen
  8, //fourteen
  7, //fifteen
  7, //sixteen
  9, //seventeen
  8, //eighteen
  8, //nineteen
};

static int ty[] = {
  6, //twenty
  6, //thirty
  5, //forty
  5, //fifty
  5, //sixty
  7, //seventy
  6, //eighty
  6, //ninety
};

static int spell1(int n) {
  int a, b;
  if (n < 20) return to20[n];

  a = n / 10;
  b = n % 10;
  return ty[a - 2] + to20[b];
}

static int spell2(int n) {
  int h, d;
  if (n < 100) return spell1(n);
  
  h = n / 100;
  d = n % 100;
  d = spell1(d);
  if (!d) return to20[h] + 7; // hundred
  return to20[h] + 10 + d; // hundredand
}

static int spell3(int n) {
  int t, h;
  if (n < 1000) return spell2(n);

  t = n / 1000;
  h = n % 1000;
  h = spell2(h);
  if (!h) return spell2(t) + 8; // thousand
  return spell2(t) + 11 + h; // thousandand
}

void pe17(int n) {
  int i, s = 0;
  
  if (n > 99999) {
    fprintf(stderr, "too large.\n");
    return;
  }
  
  for (i = 1; i < n + 1; ++i) {
    s += spell3(i);
  }
  
  printf("%d letters\n", s);
}

int pe17_main(void) {
  int n;

  while (1) {
    printf("below: ");
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (!n) {
        break;
      }
      pe17(n);
    }
  }

  return 0;
}
