#include "counter.h"

HANDLE Counter::hThread[THREAD_LENGTH - 1] = {0};
DWORD Counter::dwThreadID[THREAD_LENGTH - 1] = {0};

void Counter::Count()
{
    if (!Create(THREAD_LENGTH)) {
        Close(THREAD_LENGTH);
        return;
    }

    DWORD dwWait = ::WaitForMultipleObjects(THREAD_LENGTH, hThread, TRUE, INFINITE);
    if (dwWait != WAIT_OBJECT_0) { fprintf(stderr, "failed WaitForMultipleObjects\n"); }
   
    Close(THREAD_LENGTH);
}

bool Counter::Create(int nMax)
{
    for (int i = 0; i < nMax; ++i) {
        hThread[i] = CreateThread(NULL, 0,
                        (LPTHREAD_START_ROUTINE)ThreadProc,
                        (LPVOID)i, 0, &dwThreadID[i]);
        if (!hThread[i]) {
            return false;
        }
    }

    return true;
}

void Counter::Close(int nMax)
{
    for (int i = 0; i < nMax; ++i) {
        if (hThread[i]) {
            CloseHandle(hThread[i]);
        }
    }
}

void Counter::ThreadProc(int nThreadNo)
{
    for (int i = 1; i < 7; ++i) {
        printf("Thread %d: %d\n", nThreadNo, i);
    }
    printf("Thread %d: Nana\n", nThreadNo);

    ::ExitThread(0);
}
