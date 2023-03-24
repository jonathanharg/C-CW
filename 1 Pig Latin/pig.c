#include "pig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* VOWELS = "aeiou";

char* pig(char* word) {
    /* TODO: Add comments for inputs and outputs and what the function does */
    /* TODO: Lowercase every letter */
    unsigned short wordLen = strlen(word);
    unsigned short firstVowelIndex = wordLen;
    unsigned short foundVowel = 0;
    unsigned short i;

    for (i = 0; (i < wordLen) && !foundVowel; i++) {
        /* if the i th letter of the word is a regular vowel */
        if (strchr(VOWELS, word[i]) != NULL) {
            firstVowelIndex = i;
            foundVowel = 1;
        }

        if (i != 0 && word[i] == 'y') {
            firstVowelIndex = i;
            foundVowel = 1;
        }
    }

    unsigned short suffixLen = (firstVowelIndex == 0) ? 3 : 2;
    char* suffix = (firstVowelIndex == 0) ? "way" : "ay";

    char* p_result = malloc((wordLen + suffixLen) * sizeof(char));
    if (p_result == NULL)
        fprintf(stderr,
                "Failed to allocate enough memory for the pig latin word!");

    if (firstVowelIndex == wordLen) {
        fprintf(stderr, "Warning! Consonants only word detected!\n");
        return word;
    }

    /* Copy the first vowel onwards to the beginning of the result */
    strcpy(p_result, word + firstVowelIndex);
    /* Then append everything that comes after the vowel to the result */
    strncpy(p_result + (wordLen - firstVowelIndex), word, firstVowelIndex);
    /* Finally append the relevant suffix */
    strcpy(p_result + wordLen, suffix);

    return p_result;
}
