#include <stdio.h>
#include <stdlib.h>
#include "pig.h"

int main() {
    char* test_words[] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};

    int i;
    for (i = 0; i < sizeof(test_words) / sizeof(test_words[0]); i++) {
        char* p_word = test_words[i];
        char* p_pigged_word = pig(p_word);
        printf("%s => %s\n", p_word, p_pigged_word);
        free(p_pigged_word);
    }

    return 0;
}
