/*
 * pe19.c
 * http://kittttttan.web.fc2.com/c/pe19
 */
#include <pe19.h>

#include <stdio.h>
#include <stdlib.h>

enum {
  SUN,
  MON,
  TUE,
  WED,
  THU,
  FRI,
  SAT
};

int isLeapYear(int year) {
  return (year & 3) == 0 && (year % 100 || (year % 400) == 0);
}

int daysOfMonth(int year, int month) {
  switch (month) {
    case 2:
      return isLeapYear(year) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
  }
  
  return 31;
}

void pe19(int n) {
  int sum = 0;
  int dow = TUE;  // 1901-01-01 is Tuesday
  int year;
  int month;

  for (year = 1901; year <= n; ++year) {
    for (month = 1; month <= 12; ++month) {
      dow += daysOfMonth(year, month);
      dow %= 7;
      if (dow == SUN) ++sum;
    }
  }
  
  printf("%d (1901 to %d)\n", sum, n);
}

int pe19_main(void) {
  int n;

  while (1) {
    printf("1901 to: ");
    
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number.");
    } else {
      if (n < 1) {
        break;
      }
      pe19(n);
    }
  }

  return 0;
}
