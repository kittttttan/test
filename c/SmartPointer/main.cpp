#include <memory>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

struct S {
    int n;
};

typedef std::tr1::shared_ptr<S> S_Ptr;

int main(int argc, char** argv) {
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif

    S_Ptr s(new S);
    S_Ptr arr(new S[3], std::default_delete<S[]>());
    arr.get()[0].n = 7;

    S* s_raw = new S;
    S* arr_raw = new S[3];
    arr_raw[0].n = 7;

    delete s_raw;
    delete [] arr_raw;

    return 0;
}