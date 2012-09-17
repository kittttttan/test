#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct _Iterator Iterator;
struct _Iterator {
    Iterator* prev;
    Iterator* next;
    void* value;
};

typedef struct _List {
    size_t _size;
    Iterator* begin;
    Iterator* end;
} List;

void initIterator(Iterator* iter);
void initList(List* list);
void pushList(List* list, void* value, size_t size);
void unshiftList(List* list, void* value, size_t size);
void popList(List* list);
void shiftList(List* list);
void reverseList(List* list);
void clearList(List* list);
void freeList(List* list);

#ifdef __cplusplus
}
#endif