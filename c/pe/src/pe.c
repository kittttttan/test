#include <pe1.h>
#include <pe2.h>
#include <pe3.h>
#include <pe4.h>
#include <pe5.h>
#include <pe6.h>
#include <pe7.h>
#include <pe8.h>
#include <pe9.h>
#include <pe10.h>
#include <pe11.h>
#include <pe12.h>
#include <pe13.h>
#include <pe14.h>
#include <pe15.h>
#include <pe16.h>
#include <pe17.h>
#include <pe18.h>
#include <pe19.h>
#include <pe20.h>
#include <pe21.h>
#include <pe22.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pe(int n) {
  switch (n) {
  case 1: pe1_main(); break;
  case 2: pe2_main(); break;
  case 3: pe3_main(); break;
  case 4: pe4_main(); break;
  case 5: pe5_main(); break;
  case 6: pe6_main(); break;
  case 7: pe7_main(); break;
  case 8: pe8_main(); break;
  case 9: pe9_main(); break;
  case 10: pe10_main(); break;
  case 11: pe11_main(); break;
  case 12: pe12_main(); break;
  case 13: pe13_main(); break;
  case 14: pe14_main(); break;
  case 15: pe15_main(); break;
  case 16: pe16_main(); break;
  case 17: pe17_main(); break;
  case 18: pe18_main(); break;
  case 19: pe19_main(); break;
  case 20: pe20_main(); break;
  case 21: pe21_main(); break;
  case 22: pe22_main(); break;
  default: printf("Invalid problem number\n"); break;
  }
}

static void help() {
  printf("  pe [problem_number]\n");
}

int main(int argc, char** argv) {
  int n;

  if (argc > 1) {
    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
      help();
      return 0;
    }
    
    n = atoi(argv[1]);
    pe(n);
    return 0;
  }

  while (1) {
    printf("Problem: ");
    
    if (scanf("%d", &n) != 1) {
      scanf("%*s");
      puts("Input Number. Below 0 to exit.");
    } else {
      if (n < 1) {
        break;
      }
      pe(n);
    }
  }

  return 0;
}