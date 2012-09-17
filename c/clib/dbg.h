#pragma once

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define InitDbg _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF)
#define EndDbg  system("pause")
#else
#define InitDbg ((void *)0)
#define EndDbg  ((void *)0)
#endif
