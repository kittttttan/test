#pragma once

#include <Windows.h>
#include <stdio.h>

#define THREAD_LENGTH 3

#ifdef __cplusplus
extern "C" {
#endif

BOOL Create(int);
void Close(int);
void ThreadProc(int);
void Count();

#ifdef __cplusplus
}
#endif
