#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "list.h"

void initIterator(Iterator* iter) {
    iter->prev = NULL;
    iter->next = NULL;
    iter->value = NULL;
}

void initList(List* list) {
    list->_size = 0;
    list->begin = 
    list->end = NULL;
}

static void _pushListFirst(List* list, void* value, size_t size) {
    list->begin = (Iterator*)malloc(sizeof(Iterator));
    list->begin->prev = NULL;
    list->begin->next = NULL;
    list->begin->value = malloc(size);
    memcpy(list->begin->value, value, size);
    list->end = list->begin;
    list->_size = 1;
}

void pushList(List* list, void* value, size_t size) {
    if (!list->_size) {
        _pushListFirst(list, value, size);
        return;
    }

    list->end->next = (Iterator*)malloc(sizeof(Iterator));
    list->end->next->prev = list->end;
    list->end->next->next = NULL;
    list->end->next->value = malloc(size);
    memcpy(list->end->next->value, value, size);
    list->end = list->end->next;

    ++list->_size;
}

void unshiftList(List* list, void* value, size_t size) {
    if (!list->_size) {
        _pushListFirst(list, value, size);
        return;
    }

    list->begin->prev = (Iterator*)malloc(sizeof(Iterator));
    list->begin->prev->prev = NULL;
    list->begin->prev->next = list->begin;
    list->begin->prev->value = malloc(size);
    memcpy(list->begin->prev->value, value, size);
    list->begin = list->begin->prev;

    ++list->_size;
}

void popList(List* list) {
    Iterator* iter;

    if (!list->_size) {
        return;
    }

    iter = list->end;
    list->end = iter->prev;
    free(iter->value);
    free(iter);

    list->end->next = NULL;

    --list->_size;
}

void shiftList(List* list) {
    Iterator* iter;

    if (!list->_size) {
        return;
    }

    iter = list->begin;
    list->begin = iter->next;
    free(iter->value);
    free(iter);

    list->begin->prev = NULL;

    --list->_size;
}

void reverseList(List* list) {
    Iterator* newBeg = list->end;
    Iterator* iter = list->begin;
    Iterator* prev;
    Iterator* next;
    while (iter) {
        next = iter->next;
        prev = iter->prev;
        iter->next = prev;
        iter->prev = next;
        iter = next;
    }

    list->end = list->begin;
    list->begin = newBeg;
}

void clearList(List* list) {
    Iterator* iter = list->begin;
    Iterator* next;
    while (iter) {
        next = iter->next;
        free(iter->value);
        free(iter);
        iter = next;
    }
    list->begin = list->end = NULL;
    list->_size = 0;
}

void freeList(List* list) {
    clearList(list);
}

#ifdef __cplusplus
}
#endif