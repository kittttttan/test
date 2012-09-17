#include "stdafx.h"

#ifdef _MSC_VER
#define PRIdS "Id"
#else
#define PRIdS "zd"
#endif

int main(void) {
    printf("char: %" PRIdS "\n", sizeof(char));
    printf("short: %" PRIdS "\n", sizeof(short));
    printf("int: %" PRIdS "\n", sizeof(int));
    printf("long: %" PRIdS "\n", sizeof(long));
    printf("long long: %" PRIdS "\n", sizeof(long long));
    printf("pointer: %" PRIdS "\n", sizeof(void*));
    printf("bool: %" PRIdS "\n", sizeof(bool));

#ifdef _MSC_VER
    system("pause");
#endif
  
	return 0;
}

