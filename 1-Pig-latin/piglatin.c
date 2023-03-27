#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pig.h"
#define BUFFER_SIZE 256

int main() {
    /* TODO: This needs commenting */
    char input[BUFFER_SIZE];

    printf("Enter your input to translate: ");
    fgets(input, BUFFER_SIZE, stdin);

    while (strcmp(input, "\n") != 0) {
        input[strcspn(input, "\r\n")] = 0;
        char* word;
        word = strtok(input, " ");

        while (word != NULL) {
            char* pigged_word = pig(word);
            printf("%s ", pigged_word);
            word = strtok(NULL, " ");
            free(pigged_word);
        }
        printf("\nEnter your input to translate: ");
        fgets(input, BUFFER_SIZE, stdin);
    }
    return 0;
}
