#include "riffle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Riffle shuffle an array once in place. Make sure to call srand() first.
 * @param L The array to riffle shuffle.
 * @param len The number of elements in the array L.
 * @param size The size of each element in array L.
 * @param work An L sized buffer to work in.
 */
void riffle_once(void* L, int len, int size, void* work) {
    memcpy(work, L, len * size);
    char* p_shuffled = L;
    char* p_middle = work + ((len / 2) * size);
    char* p_end = work + (len * size);

    char* p_deckA = work;
    char* p_deckB = p_middle;

    char selected = rand() % 2;

    while (p_deckA < p_middle || p_deckB < p_end) {
        if (selected == 0) {
            /* Shuffling a card from Deck A */
            memcpy(p_shuffled, p_deckA, size);
            p_shuffled += size;
            p_deckA += size;
        }

        if (selected == 1) {
            /* Shuffling a card from Deck B */
            memcpy(p_shuffled, p_deckB, size);
            p_shuffled += size;
            p_deckB += size;
        }

        if (p_deckA >= p_middle) {
            /* If there are no more cards left in deck A, choose B */
            selected = 1;
        } else if (p_deckB >= p_end) {
            /* If there are no more cards left in deck B, choose A */
            selected = 0;
        } else {
            /* If both A & B have cards, choose randomly */
            selected = rand() % 2;
        }
    }
}

/**
 * @brief Riffle shuffle an array once in place. Make sure to call srand() first.
 * @param L The array to riffle shuffle.
 * @param len The number of elements in the array L.
 * @param size The size of each element in array L.
 * @param N How many times to shuffle the array.
 */
void riffle(void* L, int len, int size, int N) {
    void* work = malloc(size * len);
    if (work == NULL)
        fprintf(stderr, "Failed to allocate enough memory to riffle shuffle.\n");

    int n;
    for (n = 0; n < N; n++) {
        riffle_once(L, len, size, work);
    }
    // free(work);
}

/**
 * @brief Check that riffle shuffle works successfully. Make sure to call srand() first.
 * @param L The array to riffle shuffle.
 * @param len The number of elements in the array L.
 * @param size The size of each element in array L.
 * @param cmp A comparison function between elements. Should return -1, 0 or +1 if the first
 * argument is greater than, equal to, or less than the second argument respectively.
 * @return Returns 1 if the shuffle is valid, 0 otherwise.
 */
int check_shuffle(void* L, int len, int size, int (*cmp)(void*, void*)) {
    void* shuffled = malloc(len * size);
    if (shuffled == NULL) {
        fprintf(stderr, "Cannot allocate enough memory to shuffle.\n");
        return 0;
    }

    memcpy(shuffled, L, len * size);
    riffle(shuffled, len, size, 1);

    int i;
    for (i = 0; i < len; i++) {
        void* p_not_shuffled = L + (i * size);
        void* p_shuffled = shuffled + (i * size);

        /* Checks ith item in shuffled is in not shuffled and vice-versa */
        int in_shuffled = element_in(p_not_shuffled, shuffled, len, size, cmp);
        int in_not_shuffled = element_in(shuffled, L, len, size, cmp);

        if (!in_shuffled || !in_not_shuffled) {
            /* There exists an element in one set that does not exist in the other */
            free(p_shuffled);
            return 0;
        }
    }
    /* By this point, every element in the shuffled set exists in the not
     * shuffled set and vice-versa. Therefore, the shuffled set and not shuffled
     * set are equal. */
    free(shuffled);
    return 1;
}

/**
 * @brief Print an array of integers to stdout.
 * @param first_int Pointer to the first integer.
 * @param length The number of integers to print.
 */
void print_ints(int* first_int, int length) {
    printf("[");
    int i;
    printf("%d", *first_int);
    for (i = 1; i < length; i++) {
        printf(", %d", first_int[i]);
    }
    printf("]\n");
}

/**
 * @brief Print an array of char pointers to stdout.
 * @param first_str Pointer to the first char pointer.
 * @param length The number of char pointers to print.
 */
void print_strings(char** first_str, int length) {
    printf("[");
    int i;
    printf("\"%s\"", first_str[0]);
    for (i = 1; i < length; i++) {
        printf(", \"%s\"", first_str[i]);
    }
    printf("]\n");
}

/**
 * @brief Check if an element is in a set of the same type.
 * @param element The element to check if it exists in the set.
 * @param set The set of elements to check.
 * @param len The number of elements in the set.
 * @param size The size of each element in the set.
 * @param cmp A comparison function between elements. Should return -1, 0 or +1 if the first
 * argument is greater than, equal to, or less than the second argument respectively.
 * @return Returns 1 if the element is in the set, 0 otherwise.
 */
int element_in(void* element, void* set, int len, int size, int (*cmp)(void*, void*)) {
    void* p_end = set + (len * size);
    void* p;
    for (p = set; p < p_end; p += size) {
        if (cmp(p, element) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Compare two integers.
 * @param a First integer.
 * @param b Second integer.
 * @return Returns -1, 0 or +1 if the first argument is greater than, equal to, or less than the
 * second argument respectively.
 */
int int_cmp(void* a, void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_a > int_b) - (int_a < int_b);
}

/**
 * @brief Compare two strings.
 * @param a First string.
 * @param b Second string.
 * @return Returns 0 if the first string equals the second.
 */
int str_cmp(void* a, void* b) {
    return strcmp((char*)a, (char*)b);
}

/**
 * @brief Determines the quality a shuffled array of integers.
 * @param numbers The array of integers to analyze.
 * @param len The number of integers in the array.
 * @return The quality of the shuffle from 0 to 1. Should aim to be around 0.5.
 */
float quality(int* numbers, int len) {
    int* p_penultimate = numbers + len - 1;
    int count = 0;
    int* p;
    for (p = numbers; p < p_penultimate; p++) {
        int* p_next = p + 1;
        if (*p_next > *p)
            count += 1;
    }
    float result = (float)count / (len - 1);
    return result;
}

/**
 * @brief Determine the average quality of a shuffle of N integers. Make sure to call srand() first.
 * @param N The number of integers to shuffle.
 * @param shuffles The number of times to shuffle the array.
 * @param trials The number of trials to perform.
 */
void average_quality(int N, int shuffles, int trials) {
    int deck[N];
    int t;
    float total_score = 0;

    for (t = 0; t < trials; t++) {
        /* Populate the deck/Reset the deck after shuffling */
        int n;
        for (n = 0; n < N; n++) {
            deck[n] = n;
        }

        riffle(deck, N, sizeof(int), shuffles);
        total_score += quality(deck, N);
    }

    float result = total_score / trials;
    printf("Shuffled %i ints %i times over %i trials. Quality: %f\n", N, shuffles, trials, result);
}