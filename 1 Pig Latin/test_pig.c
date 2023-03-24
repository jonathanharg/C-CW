#include <stdio.h>
#include <stdlib.h>
#include "pig.h"

int main() {
    char* testWords[] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};

    int i;
    for(i = 0; i < sizeof(testWords)/sizeof(testWords[0]); i++){
        char* word = testWords[i];
        char* pigged_word = pig(word);
        printf("%s => %s\n", word, pigged_word);
        free(pigged_word);
    }

    return 0;
}
