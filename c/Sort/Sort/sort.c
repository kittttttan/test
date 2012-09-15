#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sort.h"

#define SWAP(arr, i, j) do {    \
    int t = arr[i];             \
    arr[i] = arr[j];            \
    arr[j] = t;                 \
} while(0);

void array_print(FILE* fp, int* arr, size_t length) {
    size_t i;

    if (length < 1) return;
    for (i = 0; i < length - 1; ++i) {
        fprintf(fp, "%d, ", arr[i]);
    }
    fprintf(fp, "%d\n", arr[length - 1]);
}

void array_println(FILE* fp, int* arr, size_t length) {
    size_t i;

    for (i = 0; i < length; ++i) {
        fprintf(fp, "%d\n", arr[i]);
    }
}

void array_copy(int* dest, int* src, size_t length) {
    memcpy(dest, src, sizeof(int) * length);
}

void array_inc(int* arr, size_t length) {
    size_t i;

    for (i = 0; i < length; ++i) {
        arr[i] = i;
    }
}

void array_linear(int* arr, size_t length, int ini, int step) {
    size_t i;

    for (i = 0; i < length; ++i) {
        arr[i] = i * step + ini;
    }
}

void array_rand(int* arr, size_t length, int min, int max) {
    size_t i;

    for (i = 0; i < length; ++i) {
        arr[i] = rand() % (max - min) + min;
    }
}

void array_shuffle(int* arr, size_t length) {
    size_t i, r;

    for (i = 0; i < length; ++i) {
        r = rand() % length;
        SWAP(arr, i, r);
    }
}

void sort_bubble(int* arr, size_t length) {
    size_t i, j;

    if (length < 2) return;

    for (i = 0; i < length - 1; ++i) {
        for (j = 0; j < length - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                SWAP(arr, j, j + 1);
            }
        }
    }
}

void sort_shaker(int* arr, size_t length) {
    size_t i, first, last, lastSwap;

    if (length < 2) return;

    first = 0;
    last = length - 1;

    while (1) {
        lastSwap = first;
        for (i = first; i < last; ++i){
            if (arr[i] > arr[i + 1]) {
                SWAP(arr, i, i + 1);
                lastSwap = i;
            }
        }
        last = lastSwap;
        if (first == last) { break; }

        lastSwap = last;
        for (i = last; i > first; --i) {
            if (arr[i] < arr[i - 1]) {
                SWAP(arr, i, i - 1);
                lastSwap = i;
            }
        }
        first = lastSwap;
        if (first == last) { break; }
    }
}

void sort_comb(int* arr, size_t length) {
    size_t i, h, swaps;

    if (length < 2) return;

    h = (size_t)floor(length / 1.3);
    while (1) {
        swaps = 0;
        for (i = 0; i + h < length; ++i){
            if (arr[i + h] < arr[i]) {
                SWAP(arr, i + h, i);
                ++swaps;
            }
        }
        if (h <= 1) {
            if (swaps == 0) { break; }
        } else {
            h = (size_t)floor(h / 1.3);
        }
    }
}

void sort_select(int* arr, size_t length) {
    size_t i, j, iMin;
    int min;

    if (length < 2) return;

    for (i = 0; i < length - 1; ++i) {
        iMin = i;
        min = arr[i];
        for (j = i + 1; j < length; ++j) {
            if (arr[j] < min) {
                iMin = j;
                min = arr[j];
            }
        }
        SWAP(arr, iMin, i);
    }
}

void sort_insert(int* arr, size_t length) {
    size_t i, j;

    if (length < 2) return;

    for (i = 1; i < length; ++i) {
        for (j = i; j > 0; --j) {
            if (arr[j - 1] <= arr[j]) { break; }
            SWAP(arr, j - 1, j);
        }
    }
}

void sort_shell(int* arr, size_t length) {
    size_t i, j, k;

    if (length < 2) return;

    for (i = length >> 1; i >= 1; i >>= 1){
        for (j = i; j < length; j++){
            for (k = j; k >= i; k -= i) {
                if (arr[k - i] <= arr[k]) { break; }
                SWAP(arr, k - i, k);
            }
        }
    }
}

static void _sort_quick(int* arr,
                        size_t first, size_t last) {
    size_t i = first;
    size_t j = last;
    int filter = (arr[i] + arr[j]) / 2;

    while (i < j) {
        while (arr[i] < filter) { ++i; }
        while (arr[j] > filter) { --j; }
        if (i < j) {
            SWAP(arr, i, j);
            ++i;
            --j;
        }
    }
    if (i == j) {
        if (arr[i] < filter) {
            ++i;
        } else if (arr[j] > filter) {
            --j;
        }
    }
    if (i >= first + 2) { _sort_quick(arr, first, i - 1); }
    if (j + 2 <= last) { _sort_quick(arr, j + 1, last); }
}

void sort_quick(int* arr, size_t length) {
    if (length < 2) return;

    _sort_quick(arr, 0, length - 1);
}

void sort_bucket(int* arr, size_t length, int min, int max) {
    size_t i, l, size;
    int* buckets;

    if (length < 2) return;

    size = max - min + 1;
    if (size < 2) return;
    buckets = (int*)malloc(sizeof(int) * size);

    for (i = 0; i < size; ++i) {
        buckets[i] = 0;
    }
    for (i = 0; i < length; ++i) {
        ++buckets[arr[i] - min];
    }
    for (i = 0, l = 0; l < size; ++l){
        while (buckets[l] > 0) {
            arr[i] = l;
            ++i;
            --buckets[l];
        }
    }

    free(buckets);
}
