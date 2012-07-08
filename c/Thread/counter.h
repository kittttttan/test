#pragma once

#include <Windows.h>
#include <stdio.h>

#define THREAD_LENGTH 3

class Counter {
public:
    Counter() : count(0) {}
    ~Counter() {}

    void Count();
    bool Create(int);
    void Close(int);

    static void ThreadProc(int);

private:
    static HANDLE hThread[THREAD_LENGTH - 1];
    static DWORD dwThreadID[THREAD_LENGTH - 1];

    int count;
};

