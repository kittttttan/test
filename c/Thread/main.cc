//#include "count.h"
#include "counter.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

int main(int argc, char** argv)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif

    // Count();
    {
        Counter counter;
        counter.Count();
    }

    system("pause");

    return 0;
}
