#pragma once

void array_print(FILE* fp, int* arr, size_t length);
void array_println(FILE* fp, int* arr, size_t length);
void array_copy(int* dest, int* src, size_t length);
void array_inc(int* arr, size_t length);
void array_linear(int* arr, size_t length, int ini, int step);
void array_rand(int* arr, size_t length, int min, int max);
void array_shuffle(int* arr, size_t length);

void sort_bubble(int* arr, size_t length);
void sort_shaker(int* arr, size_t length);
void sort_comb(int* arr, size_t length);
void sort_select(int* arr, size_t length);
void sort_insert(int* arr, size_t length);
void sort_shell(int* arr, size_t length);
void sort_quick(int* arr, size_t length);
void sort_bucket(int* arr, size_t length, int min, int max);
