#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../2-Shuffling/riffle.h"
#include "beggar.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide the number of players as an argument\n");
        printf("\nUsage: single N\nN:    int - number of players.\n");
        return 1;
    }

    int Nplayers = atoi(argv[1]);

    if (Nplayers < 2 || Nplayers > 25) {
        fprintf(stderr, "At least 2 players are needed to play the game (and no more than 25).\n");
        return 1;
    }

    int pack[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

    srand(time(NULL));
    riffle(pack, 52, sizeof(int), 7);

    beggar(Nplayers, pack, 1);
    return 0;
}