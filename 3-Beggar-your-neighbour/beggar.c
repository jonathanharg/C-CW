#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../2-Shuffling/riffle.h"
#include "beggar.h"

int main() {
    int pack[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    srand(time(NULL));
    riffle(pack, 52, sizeof(int), 7);

    beggar(3, pack, 1);
    return 0;
}

int beggar(int Nplayers, int* deck, int talkative) {
    Hand* players[Nplayers];
    Hand* pile = hand_create();

    int i;
    for (i = 0; i < Nplayers; i++) {
        players[i] = hand_create();
    }

    // Dealing
    for (i = 0; i < 52; i++) {
        Hand* give_to = players[i % Nplayers];
        hand_push(give_to, deck[i]);
    }

    int player = 0;
    int last_player = 0;
    unsigned long int turn = 1;
    while (!finished(players, Nplayers)) {
        if (players[player]->empty) {
            // The player has no cards, skip them
            player = (player + 1) % Nplayers;
            continue;
        }

        if (talkative) {
            printf("Turn %lu\n", turn);
            printf("Pile:  ");
            print_ints(pile->start, 52);
            for (i = 0; i < Nplayers; i++) {
                if (i == player) {
                    printf("*");
                } else {
                    printf(" ");
                }
                printf("%4i: ", i);
                print_ints(players[i]->start, 52);
            }
        }

        Hand* reward = take_turn(players[player], pile);
        if (reward != NULL) {
            hand_give_pile(players[last_player], reward);
        }

        // Save the last player, incase a player is eliminated
        // Then we always know the last player
        last_player = player;
        turn++;
        player = (player + 1) % Nplayers;
    }
    printf("Turns: %lu", turn);

    for (i = 0; i < Nplayers; i++) {
        free(players[i]->start);
        free(players[i]);
    }
    free(pile);
    return 0;
}

Hand* hand_create() {
    Hand* hand = malloc(sizeof(Hand));
    /* The size of a players hand cannot exceed 52 */
    int* start = (int*)malloc(52 * sizeof(int));
    if (start == NULL || hand == NULL)
        fprintf(stderr, "Failed to allocate enough memory to create a hand.\n");
    hand->start = start;
    hand->end = start + 51;
    hand->top = start;
    hand->tail = start;
    hand->empty = 1;
    return hand;
}

void hand_push(Hand* self, int card) {
    // If the tail is the same as the top and the hand isn't uninitialized
    if ((self->tail == self->top) && !self->empty) {
        fprintf(stderr,
                "Hand is full! Cannot add another card without overwriting an "
                "existing one!\n");
        return;
    }
    self->empty = 0;
    *(self->tail) = card;
    if (self->tail == self->end) {
        // We have reached the end of the array, wrap back around to the
        // beginning
        self->tail = self->start;
    } else {
        self->tail += 1;
    }
}

int finished(Hand** players, int Nplayers) {
    int has_cards = -1;
    int eliminated = 0;
    int i;
    for (i = 0; i < Nplayers; i++) {
        if (players[i]->empty) {
            eliminated += 1;
            continue;
        }
        if (has_cards != -1) {
            // There is already another player with cards
            return 0;
        }
        has_cards = i;
    }
    // Only one player has any cards remaining, they have won.
    // printf("Player %i has won!\n", has_cards);
    return 1;
}

int hand_peek(Hand* self) {
    int* last = self->tail - 1;
    return *last;
}

int hand_pop(Hand* self) {
    if (self->empty) {
        return 0;
    }

    if (self->tail == self->start) {
        self->tail = self->end;
    } else {
        self->tail -= 1;
    }

    if (self->top == self->tail) {
        self->empty = 1;
    }

    int popped = *(self->tail);
    *(self->tail) = 0;
    return popped;
}

Hand* take_turn(Hand* player, Hand* pile) {
    int top_pile = hand_peek(pile);
    int give_reward = 0;
    int penalty;
    // if (top_pile == 0) {
    //     printf("The pile is empty, ");
    // } else {
    //     printf("Top card in pile is %i, ", top_pile);
    // }

    if (top_pile < 11) {
        penalty = 1;
        // printf("so we should lay a single card. ");
    } else {
        penalty = top_pile - 10;
        // We must reward the previous player the pile
        // unless we play a penalty card.
        give_reward = 1;
        // if (penalty == 1)
        //     printf("so we should lay 1 card. ");
        // else
        //     printf("so we should lay %i cards. ", penalty);
    }
    for (; penalty > 0; penalty--) {
        int card = hand_pop(player);

        if (card == 0) {
            // printf("We are out of cards! ");
            // This player is out of cards, and is therefore out of the game.
            break;
        }

        // printf("Adding %i to pile. ", card);

        hand_push(pile, card);

        if (card > 10) {
            // printf("We played a penalty card! ");
            give_reward = 0;
            break;
        }
    }
    if (give_reward) {
        // printf(
        //     "We never played a penalty card! Giving the pile to the previous "
        //     "player!\n\n");
        return pile;
    }
    // printf("\n\n");

    return NULL;
}

void hand_give_pile(Hand* hand, Hand* pile) {
    for (; pile->top < pile->tail; pile->top += 1) {
        hand->top -= 1;
        if (hand->top < hand->start) {
            // We've overflowed, loop back around to the end;
            hand->top = hand->end;
        }
        *(hand->top) = *(pile->top);
    }
    pile->top = pile->start;
    pile->tail = pile->start;
    pile->empty = 1;
    int i;
    for (i = 0; i < 52; i++) {
        pile->start[i] = 0;
    }
}