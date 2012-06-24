#include "stdafx.h"

#ifdef _MSC_VER
static void MIE_MEM_Init()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_DELAY_FREE_MEM_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}

#define PRIdS "Id"
#else
#define PRIdS "zd"
#endif

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _MSC_VER
  MIE_MEM_Init();
#endif

	printf("char: %" PRIdS "\n", sizeof(char));
	printf("short: %" PRIdS "\n", sizeof(short));
	printf("int: %" PRIdS "\n", sizeof(int));
	printf("long: %" PRIdS "\n", sizeof(long));
	printf("long long: %" PRIdS "\n", sizeof(long long));
	printf("pointer: %" PRIdS "\n", sizeof(void*));
	printf("bool: %" PRIdS "\n", sizeof(bool));

  getchar();

	return 0;
}

