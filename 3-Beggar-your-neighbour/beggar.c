#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "beggar.h"
#include "../2-Shuffling/riffle.h"

int main(){
    int pack[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    // riffle(pack, 52, sizeof(int), 7);

    beggar(3, pack, 1);
}

int beggar(int Nplayers, int* deck, int talkative) {
    Hand* players[Nplayers];
    Hand* pile = hand_create();

    int i;
    for (i = 0; i < Nplayers; i++) {
        players[i] = hand_create();
    }

    for (i = 0; i < 52; i++) {
        Hand* give_to = players[i % Nplayers];
        hand_push(give_to, deck[i]);
    }

    // print_ints(players[0]->start, 52);
    return 0;
}

void talk(int talkative, const char* format, ...) {
    va_list args;
    va_start(args, format);

    if (talkative)
        vprintf(format, args);
    va_end(args);
}

Hand* hand_create() {
    Hand* hand = malloc(sizeof(hand));
    /* The size of a players hand cannot exceed 52 */
    int* start = (int*)malloc(52 * sizeof(int));
    if (start == NULL || hand == NULL)
        fprintf(stderr, "Failed to allocate enough memory to create a hand.");
    hand->head = start;
    hand->start = start;
    hand->tail = start;
    return hand;
}

void hand_push(Hand* self, int card){
    *(self->tail) = card;
    self->tail += 1;
}