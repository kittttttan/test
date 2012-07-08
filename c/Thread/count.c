#include "count.h"

#ifdef __cplusplus
extern "C" {
#endif

static HANDLE hThread[THREAD_LENGTH - 1];
static DWORD dwThreadID[THREAD_LENGTH - 1];

void Count()
{
    if (!Create(THREAD_LENGTH)) {
        Close(THREAD_LENGTH);
        return;
    }

    WaitForMultipleObjects(THREAD_LENGTH, hThread, TRUE, INFINITE);
   
    Close(THREAD_LENGTH);
}

BOOL Create(int nMax)
{
    int i, c;
    for (i = 0; i < nMax; ++i) {
        hThread[i] = CreateThread(NULL, 0,
                        (LPTHREAD_START_ROUTINE)ThreadProc,
                        (LPVOID)i, 0, &dwThreadID[i]);
    }
   
    for (c = 0; i < nMax; ++c) {
        if (hThread[c] == NULL) {
            return FALSE;
        }
    }

    return TRUE;
}

void Close(int nMax)
{
    int i;
    for (i = 0; i < nMax; ++i) {
        if (hThread[i]) {
            CloseHandle(hThread[i]);
        }
    }

    return;
}

void ThreadProc(int nThreadNo)
{
    int i;
    for (i = 1; i < 7; ++i) {
        printf("Thread %d: %d\n", nThreadNo, i);
    }
    printf("Thread %d: Nana\n", nThreadNo);

    ExitThread(0);
}

#ifdef __cplusplus
}
#endif
