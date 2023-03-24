#include "riffle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *));
void print_ints(int* first_int, int length);
void print_strings(char** first_str, int length);
int element_in(void *element, void *set, int len, int size, int (*cmp)(void *, void *));
int int_cmp(void *a, void *b);
int str_cmp(void *a, void *b);

int main(){
    int numbers[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    char *greek[] = { "alpha" , "beta" , "gamma" , "delta" , "epsilon" , "zeta" , "eta" , "theta" , "iota" , "kappa" , "lambda" , "mu"};

    int numbers_len = sizeof(numbers)/sizeof(numbers[0]);
    int greek_len = sizeof(greek)/sizeof(greek[0]);
    int numbers_size = sizeof(numbers[0]);
    int greek_size = sizeof(greek[0]);

    riffle(numbers, numbers_len, numbers_size, 5);
    riffle(greek, greek_len, greek_size, 5);

    print_ints(numbers, numbers_len);
    print_strings((char**) &greek, greek_len);

    int numbers_check = check_shuffle(numbers, numbers_len, numbers_size, int_cmp);
    int greek_check = check_shuffle(greek, greek_len, greek_size, str_cmp);

    if (numbers_check ==1)
        printf("numbers check PASSED: x is in shuffled if and only if x is in unshuffled.\n");
    else
        fprintf(stderr, "numbers check FAILED: riffle is not a permutation!\n");

    if (greek_check==1)
        printf("greek check PASSED: x is in shuffled if and only if x is in unshuffled.\n");
    else
        fprintf(stderr, "greek check FAILED: riffle is not a permutation!\n");

    return 0;
}

int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *)){
    void* shuffled = malloc(len * size);
    if (shuffled == NULL){
        fprintf(stderr, "Cannot allocate enough memeory to shuffle.\n");
        return 0;
    }

    memcpy(shuffled, L, len * size);
    riffle(shuffled, len, size, 1);

    int i;
    for (i=0; i<len; i++){
        void *ith_unshuffled = L + (i * size);
        void *ith_shuffled = shuffled + (i * size);

        int in_shuffled = element_in(ith_unshuffled, shuffled, len, size, cmp);
        int in_unshuffled = element_in(ith_shuffled, L, len, size, cmp);
        if(!in_shuffled || !in_unshuffled){
            // There exists an element in one set that does not exist in the other
            return 0;
        }
    }
    free(shuffled);
    // By this point, every element in the shuffled set exisits in the unshuffled set
    // and vice-versa. Therefore the shuffled set and unshuffled set are equal.
    return 1;
}

void print_ints(int* first_int, int length) {
    printf("[");
    int i;
    printf("%d", *first_int);
    for (i = 1; i < length; i++) {
        printf(", %d", first_int[i]);
    }
    printf("]\n");
}

void print_strings(char** first_str, int length) {
    printf("[");
    int i;
    printf("\"%s\"", first_str[0]);
    for (i = 1; i < length; i++) {
        printf(", \"%s\"", first_str[i]);
    }
    printf("]\n");
}

int element_in(void *element, void *set, int len, int size, int (*cmp)(void *, void *)){
    void *end = set + (len * size);
    void *p;
    for(p=set; p < end; p += size){
        if (cmp(p, element)==0) {
            // element is in the set
            return 1;
        }
    }
    // Element not found in set
    return 0;
}

int int_cmp(void *a, void *b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_a > int_b) - (int_a < int_b);
}

int str_cmp(void *a, void *b) {
    return strcmp((char *)a, (char*) b);
}
