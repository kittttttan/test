/**
 * Sorting Algorithms in C
 * http://en.wikipedia.org/wiki/Sorting_algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "sort.h"

#define ARRAY_LENGTH    4096
#ifdef _MSC_VER
#define OUT_SEC "%5lu ms"
#else
#define OUT_SEC "%8lu usec"
#endif


void help() {
    printf(
        "  Sort [options]\n"
        "\n"
        "  -s             Shuffle mode\n"
        "  -o [filename]  Output to file or stdout\n"
        "  -h             Show help\n"
        );
}

int main(int argc, char* argv[]) {
    clock_t t0, t;
    FILE* fp = stdout;
    int i, out = 0, shuffle = 0;
    int arr[ARRAY_LENGTH] = {0};
    int arr_sorted[ARRAY_LENGTH] = {0};

    for (i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            help();
            goto END_MAIN;
        } else if (strcmp(argv[i], "-o") == 0) {
            out = 1;
            ++i;
            if (i >= argc) break;
            fp = fopen(argv[i], "a");
            if (!fp) {
                fprintf(stderr, "can't open %s\n", argv[i]);
                return -1;
            }
        } else if (strcmp(argv[i], "-s") == 0) {
            shuffle = 1;
        }
    }

    srand(clock());

    if (shuffle) {
        // random order
        // ex. 7, 0, 3, 2, ...
        array_inc(arr, ARRAY_LENGTH);
        array_shuffle(arr, ARRAY_LENGTH);
    } else {
        // random value
        // ex. 0, 7, 3, 0, ...
        array_rand(arr, ARRAY_LENGTH, 0, ARRAY_LENGTH);
    }

    array_copy(arr_sorted, arr, ARRAY_LENGTH);
    t0 = clock();
    sort_bubble(arr_sorted, ARRAY_LENGTH);
    t = clock();
    printf("bubble: " OUT_SEC "\n", (t - t0));

    array_copy(arr_sorted, arr, ARRAY_LENGTH);
    t0 = clock();
    sort_shaker(arr_sorted, ARRAY_LENGTH);
    t = clock();
    printf("shaker: " OUT_SEC "\n", (t - t0));

    array_copy(arr_sorted, arr, ARRAY_LENGTH);
    t0 = clock();
    sort_comb(arr_sorted, ARRAY_LENGTH);
    t = clock();
    printf("com   : " OUT_SEC "\n", (t - t0));

    array_copy(arr_sorted, arr, ARRAY_LENGTH);
    t0 = clock();
    sort_select(arr_sorted, ARRAY_LENGTH);
    t = clock();
    printf("select: " OUT_SEC "\n", (t - t0));

    array_copy(arr_sorted, arr, ARRAY_LENGTH);
    t0 = clock();
    sort_insert(arr_sorted, ARRAY_LENGTH);
    t = clock();
    printf("insert: " OUT_SEC "\n", (t - t0));

    array_copy(arr_sorted, arr, ARRAY_LENGTH);
    t0 = clock();
    sort_shell(arr_sorted, ARRAY_LENGTH);
    t = clock();
    printf("shell : " OUT_SEC "\n", (t - t0));

    array_copy(arr_sorted, arr, ARRAY_LENGTH);
    t0 = clock();
    sort_quick(arr_sorted, ARRAY_LENGTH);
    t = clock();
    printf("quick : " OUT_SEC "\n", (t - t0));

    array_copy(arr_sorted, arr, ARRAY_LENGTH);
    t0 = clock();
    sort_bucket(arr_sorted, ARRAY_LENGTH, 0, ARRAY_LENGTH);
    t = clock();
    printf("bucket: " OUT_SEC "\n", (t - t0));

    if (out) {
        array_println(fp, arr, ARRAY_LENGTH);
        fprintf(fp, "\n");
        array_println(fp, arr_sorted, ARRAY_LENGTH);
        fprintf(fp, "\n");
    }

END_MAIN:
    if (fp != stdout) fclose(fp);

#ifdef _MSC_VER
    system("pause");
#endif

    return 0;
}