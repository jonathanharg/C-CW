#include "riffle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
int main() {
    srand(time(NULL));
    // int deck[] = {1,2,3,4,5,6,7,8,9};
    int deck[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int* work = malloc(sizeof(deck));
    print_ints(deck, sizeof(deck)/sizeof(deck[0]));
    // riffle_once(deck, sizeof(deck)/sizeof(deck[0]), sizeof(deck[0]), work);
    riffle(deck, sizeof(deck)/sizeof(deck[0]), sizeof(deck[0]), 10);
    print_ints(deck, sizeof(deck)/sizeof(deck[0]));
    return 0;
}
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
            // Shuffling a card from Deck B
            memcpy(p_shuffled, p_deckB, size);
            p_shuffled += size;
            p_deckB += size;
        }

        if (p_deckA >= p_middle) {
            // If there are no more cards left in deck A, choose B
            selected = 1;
        } else if (p_deckB >= p_end) {
            // If there are no more cards left in deck B, choose A
            selected = 0;
        } else {
            // If both A & B have cards, choose randomly
            selected = rand() % 2;
        }
    }
}

void riffle(void* L, int len, int size, int N) {
    if (N <= 0) {
        fprintf(stderr,
                "N must be greater than or equal to zero to riffle shuffle.\n");
        return;
    }

    srand(time(NULL));

    void* work = malloc(size * len);
    if (work == NULL)
        fprintf(stderr,
                "Failed to allocate enough memory to riffle shuffle.\n");

    int n;
    for (n = 0; n < N; n++) {
        riffle_once(L, len, size, work);
    }
    free(work);
}
