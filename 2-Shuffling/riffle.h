#ifndef RIFFLE_H
#define RIFFLE_H
void riffle_once(void* L, int len, int size, void* work);
void riffle(void* L, int len, int size, int N);
int check_shuffle(void* L, int len, int size, int (*cmp)(void*, void*));
void print_ints(int* first_int, int length);
void print_strings(char** first_str, int length);
int element_in(void* element, void* set, int len, int size, int (*cmp)(void*, void*));
int int_cmp(void* a, void* b);
int str_cmp(void* a, void* b);
float quality(int* numbers, int len);
void average_quality(int N, int shuffles, int trials);
#endif
