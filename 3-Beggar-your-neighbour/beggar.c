#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "beggar.h"

/**
 * @brief Simulate a single game of beggar your neighbour.
 * @param Nplayers The number of player to simulate. Must be at least 2 and at most 25.
 * @param deck Pointer to the deck of 52 cards to use. Defined from top to bottom as an array
 * of integers.
 * @param talkative Whether or not to display the state of the game before each player takes
 * their turn.
 * @return Returns the number of turns it took for the game to terminate.
 */
int beggar(int Nplayers, int* deck, int talkative) {
    if (Nplayers < 2 || Nplayers > 25) {
        fprintf(stderr, "Cannot play with less than 2 players or more than 25.\n");
        return -1;
    }

    /* Initialise hands and the pile */
    Hand* players[Nplayers];
    Hand* pile = hand_create();

    int i;
    for (i = 0; i < Nplayers; i++) {
        players[i] = hand_create();
    }

    /* Deal the cards */
    for (i = 0; i < 52; i++) {
        Hand* deal_to = players[i % Nplayers];
        hand_push(deal_to, deck[i]);
    }

    /* Which player is currently playing */
    int player = 0;
    /* Which was the last player to play. Who we should give the reward to. */
    int last_player = 0;
    int turn = 0;

    while (!finished(players, Nplayers)) {
        if (players[player]->empty) {
            /* The player has no cards, skip them */
            player = (player + 1) % Nplayers;
            continue;
        }

        turn++;

        if (turn >= INT_MAX - 1)
            /* Unlikely to happen, incase an infinite game occurs. */
            fprintf(stderr, "Turn count will overflow!");

        if (talkative) {
            printf("Turn %i\n", turn);
            printf("Pile:  ");
            hand_print(pile, 0);

            for (i = 0; i < Nplayers; i++) {
                if (i == player) {
                    printf("*");
                } else {
                    printf(" ");
                }
                printf("%4i: ", i);
                hand_print(players[i], 1);
            }
            printf("\n\n");
        }

        Hand* reward = take_turn(players[player], pile);

        if (reward != NULL) {
            hand_give_pile(players[last_player], reward);
        }

        /* Save the last player, incase a player is eliminated */
        last_player = player;
        player = (player + 1) % Nplayers;
    }

    if (talkative)
        printf("Turns: %i", turn);

    for (i = 0; i < Nplayers; i++) {
        free(players[i]->start);
        free(players[i]);
    }
    free(pile->start);
    free(pile);
    return turn;
}

/**
 * @brief Determine if a game of Beggar your neighbour has finished.
 * @param players Pointer to an array of Hands.
 * @param Nplayers The number of players in the game.
 * @return Returns 1 if the game is finished, 0 otherwise.
 */
int finished(Hand** players, int Nplayers) {
    int someone_has_cards = 0;
    int i;
    for (i = 0; i < Nplayers; i++) {
        if (players[i]->empty) {
            continue;
        }
        if (someone_has_cards) {
            /* There is already another player with cards, therefore we haven't finished */
            return 0;
        }
        someone_has_cards = 1;
    }
    /* Only one player has any cards remaining, they have won. */
    return 1;
}

/**
 * @brief Take a turn given a players Hand and a pile.
 * @param player The player whose turn it is.
 * @param pile The current game pile.
 * @return The reward if the player fails to play a penalty card, NULL otherwise.
 */
Hand* take_turn(Hand* player, Hand* pile) {
    /* NOTE: For some reason Valgrind believes the follow is an error. Compiling with the -ggdb3
    flag reveals that it believes there is a "Conditional jump or move depends on uninitialised
    value(s)" at this location. The only way I have found to get rid of this error is to hard-code
    hand_peek() so that it returns a constant value i.e. 0. Somewhat ironically, this solution to
    the error also breaks the whole program. I believe this is a false positive found by Valgrind,
    but if I am wrong and you can lead me to the source of this error I would love to know. */
    int top_pile = hand_peek(pile);
    /* If we have to give out a reward the last player or not */
    int give_reward = 0;
    int penalty;

    if (top_pile < 11) {
        penalty = 1;
    } else {
        penalty = top_pile - 10;
        give_reward = 1;
    }

    for (; penalty > 0; penalty--) {
        int card = hand_pop(player);

        /* This player is out of cards, and is therefore out of the game. */
        if (card == 0)
            break;

        hand_push(pile, card);

        /*  We played a penalty card, no need to give a reward and we can stop drawing cards now. */
        if (card > 10) {
            give_reward = 0;
            break;
        }
    }

    if (give_reward)
        return pile;

    return NULL;
}
