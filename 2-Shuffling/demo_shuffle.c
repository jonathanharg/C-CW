#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "riffle.h"

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    char* greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta",
                     "eta", "theta", "iota", "kappa", "lambda", "mu"};

    int numbers_len = sizeof(numbers) / sizeof(numbers[0]);
    int greek_len = sizeof(greek) / sizeof(greek[0]);
    int numbers_size = sizeof(numbers[0]);
    int greek_size = sizeof(greek[0]);

    srand(time(NULL));

    riffle(numbers, numbers_len, numbers_size, 5);
    riffle(greek, greek_len, greek_size, 5);

    print_ints(numbers, numbers_len);
    print_strings((char**)&greek, greek_len);

    int numbers_check = check_shuffle(numbers, numbers_len, numbers_size, int_cmp);
    int greek_check = check_shuffle(greek, greek_len, greek_size, str_cmp);

    if (numbers_check == 1)
        printf("numbers check PASSED: x is in shuffled if and only if x is in not shuffled.\n");
    else
        fprintf(stderr, "numbers check FAILED: riffle is not a permutation!\n");

    if (greek_check == 1)
        printf("greek check PASSED: x is in shuffled if and only if x is in not shuffled.\n");
    else
        fprintf(stderr, "greek check FAILED: riffle is not a permutation!\n");

    return 0;
}