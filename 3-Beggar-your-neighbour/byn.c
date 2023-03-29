#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../2-Shuffling/riffle.h"
#include "beggar.h"

int PRINT_DECKS = 0;

typedef struct {
    int shortest;
    int longest;
    float average;
    int longest_deck[52];
    int shortest_deck[52];
} Statistics;

Statistics* statistics(int Nplayers, int games);
void copy_deck(int* deck, int* destination);
void write_deck(int* pack);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Please provide the number of players and the number of trials as arguments\n");
        printf("\nUsage: byn N T\nN:    int - maximum number of players.\nT:    int - number of trials.");
        return 1;
    }

    int Nplayers = atoi(argv[1]);
    int trials = atoi(argv[2]);

    if (Nplayers < 2 || Nplayers > 25) {
        fprintf(stderr, "At least 2 players are needed to play the game (and no more than 25).\n");
        return 1;
    }

    if (trials < 1) {
        fprintf(stderr, "At least 1 trial is needed to play the game\n");
        return 1;
    }

    int player_count;
    for (player_count = 2; player_count <= Nplayers; player_count++) {
        Statistics* stats = statistics(player_count, trials);
        printf("Played %i games with %i players, shortest %i, longest %i, average %f\n", trials, player_count, stats->shortest, stats->longest, stats->average);
        
        if (PRINT_DECKS) {
            printf("Shortest deck: ");
            print_ints(stats->shortest_deck, 52);
            printf("Longest deck: ");
            print_ints(stats->longest_deck, 52);
        }
        
        free(stats);
    }
}

/**
 * @brief Run X number of games of Beggar your neighbour with N players.
 * @param Nplayers The number of players to be included in each run.
 * @param games The number of games of Beggar your neighbour to run.
 * @return Pointer to a Statistics struct. Ownership is given to the caller of the function.
 */
Statistics* statistics(int Nplayers, int games) {
    Statistics* stats = (Statistics*)malloc(sizeof(Statistics));
    if (stats == NULL)
        fprintf(stderr, "Failed to allocate enough memory to store the statistics.");

    stats->shortest = -1;
    stats->longest = 0;
    unsigned long int total = 0;

    int pack[] = {14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                  14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                  14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                  14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    srand(time(NULL));

    int i;
    for (i = 0; i < games; i++) {
        riffle(pack, 52, sizeof(int), 7);
        write_deck(pack);

        int turns = beggar(Nplayers, pack, 0);
        total += turns;

        if (turns < stats->shortest || stats->shortest == -1) {
            stats->shortest = turns;
            copy_deck(pack, stats->shortest_deck);
        }

        if (turns > stats->longest) {
            stats->longest = turns;
            copy_deck(pack, stats->longest_deck);
        }
    }

    stats->average = (float)total / games;

    return stats;
}

/**
 * @brief Copy the current deck to another destination.
 * @param deck The current deck to copy.
 * @param destination The destination to copy to.
 */
void copy_deck(int* deck, int* destination) {
    int i;
    for (i = 0; i < 52; i++) {
        destination[i] = deck[i];
    }
}

/**
 * @brief Save the current deck to a .current_deck file. For Debug in case of a crash
 * or incase an infinite game is found.
 * @param pack The pack of cards to write to file.
 */
void write_deck(int* pack) {
    FILE* file = fopen(".current_deck", "w");
    int i;
    fprintf(file, "Last run deck: %d", pack[0]);
    for (i = 1; i < 52; i++) {
        fprintf(file, ", %d", pack[i]);
    }
    fclose(file);
}