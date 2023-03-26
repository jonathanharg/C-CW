#include "riffle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void riffle(void* L, int len, int size, int N) {
    if (N <= 0) {
        fprintf(stderr, "N must be greater than or equal to zero to riffle shuffle.\n");
        return;
    }

    void* work = malloc(size * len);
    if (work == NULL)
        fprintf(stderr, "Failed to allocate enough memory to riffle shuffle.\n");

    int n;
    for (n = 0; n < N; n++) {
        riffle_once(L, len, size, work);
    }
    free(work);
}

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
        void* ith_not_shuffled = L + (i * size);
        void* ith_shuffled = shuffled + (i * size);

        int in_shuffled = element_in(ith_not_shuffled, shuffled, len, size, cmp);
        int in_not_shuffled = element_in(ith_shuffled, L, len, size, cmp);

        if (!in_shuffled || !in_not_shuffled)
            /* There exists an element in one set that does not exist in the
             * other */
            return 0;
    }
    free(shuffled);
    /* By this point, every element in the shuffled set exists in the not
     * shuffled set and vice-versa. Therefore the shuffled set and not shuffled
     * set are equal. */
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

int element_in(void* element, void* set, int len, int size, int (*cmp)(void*, void*)) {
    void* end = set + (len * size);
    void* p;
    for (p = set; p < end; p += size) {
        if (cmp(p, element) == 0) {
            /* Element is in the set */
            return 1;
        }
    }
    /* Element not found in set */
    return 0;
}

int int_cmp(void* a, void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_a > int_b) - (int_a < int_b);
}

int str_cmp(void* a, void* b) {
    return strcmp((char*)a, (char*)b);
}

float quality(int* numbers, int len) {
    int* penultimate = numbers + len - 1;
    int count = 0;
    int* p;
    for (p = numbers; p < penultimate; p++) {
        int* next = p + 1;
        if (*next > *p)
            count += 1;
    }
    float result = ((float)count) / ((float)len - 1);
    return result;
}

void average_quality(int N, int shuffles, int trials) {
    /* Create deck */
    int deck[N];
    int trial;
    float total_score = 0;
    for (trial = 0; trial < trials; trial++) {
        /* Populate the deck/Reset the deck after shuffling */
        int n;
        for (n = 0; n < N; n++) {
            deck[n] = n;
        }
        riffle(deck, N, sizeof(int), shuffles);
        total_score += quality(deck, N);
    }
    float result = (total_score) / ((float)trials);
    printf("Shuffled %i ints %i times over %i trials. Quality: %f\n", N, shuffles, trials, result);
}