#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pig.h"

#define BUFFER_SIZE 256

int main() {
    char input[BUFFER_SIZE];

    printf("Enter your input to translate: ");
    fgets(input, BUFFER_SIZE, stdin);

    while (strcmp(input, "\n") != 0) {
        /* Remove newline */
        input[strcspn(input, "\r\n")] = 0;
        /* Split by space */
        char* p_word = strtok(input, " ");

        while (p_word != NULL) {
            char* p_pigged_word = pig(p_word);
            printf("%s ", p_pigged_word);
            free(p_pigged_word);

            /* Get next word */
            p_word = strtok(NULL, " ");
        }

        printf("\nEnter your input to translate: ");
        fgets(input, BUFFER_SIZE, stdin);
    }
    return 0;
}
