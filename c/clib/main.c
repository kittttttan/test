#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "dbg.h"
#include "list.h"

typedef struct _Strct {
    int value;
    char ch[24];
} Strct;

int main(int argc, char* argv[]) {
    Strct s0 = {0, "s0"}, s1 = {1, "s1"}, s2 = {2, "s2"};
    Strct* pStr;
    List list;
    Iterator* iter;

    InitDbg;

    initList(&list);

    pushList(&list, &s1, sizeof(s1));
    pushList(&list, &s2, sizeof(s2));
    unshiftList(&list, &s0, sizeof(s0));

    for (iter = list.begin; iter; iter = iter->next) {
        pStr = (Strct*)iter->value;
        printf("%d %s\n", pStr->value, pStr->ch);
    }

    printf("\nreverse\n");
    reverseList(&list);
    for (iter = list.begin; iter; iter = iter->next) {
        pStr = (Strct*)iter->value;
        printf("%d %s\n", pStr->value, pStr->ch);
    }

    printf("\npop\n");
    popList(&list);
    for (iter = list.begin; iter; iter = iter->next) {
        pStr = (Strct*)iter->value;
        printf("%d %s\n", pStr->value, pStr->ch);
    }

    printf("\nshift\n");
    shiftList(&list);
    for (iter = list.begin; iter; iter = iter->next) {
        pStr = (Strct*)iter->value;
        printf("%d %s\n", pStr->value, pStr->ch);
    }

    freeList(&list);

    EndDbg;

    return 0;
}

#ifdef __cplusplus
}
#endif