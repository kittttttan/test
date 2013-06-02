#ifdef _MSC_VER
// for Windows
#define PRIdS "Iu"
#else
// for MinGW
#ifdef _WIN32
#define _GNU_SOURCE 1
#endif
// for gcc
#define PRIdS "zu"
#endif

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("char: %" PRIdS "\n", sizeof(char));
    printf("short: %" PRIdS "\n", sizeof(short));
    printf("int: %" PRIdS "\n", sizeof(int));
    printf("long: %" PRIdS "\n", sizeof(long));
    printf("long long: %" PRIdS "\n", sizeof(long long));
    printf("pointer: %" PRIdS "\n", sizeof(void*));

#ifdef _MSC_VER
    system("pause");
#endif
  
	return 0;
}

