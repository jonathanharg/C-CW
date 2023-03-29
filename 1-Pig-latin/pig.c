#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pig.h"

const char* VOWELS = "aeiou";

/**
 * @brief Converts a word to a lowercased pig latin word.
 * @param word a pointer to the word you would like to translate.
 * @return a pointer the pig latin word. Ownership is given to the function caller.
 */
char* pig(char* word) {
    /* TODO: Fix valgrind errors */
    unsigned long int word_len = strlen(word);
    /* Default the index of the first vowel to be the end of the string, i.e. no vowel */
    int first_vowel_index = word_len;
    int found_vowel = 0;
    int i;

    for (i = 0; (i < word_len) && !found_vowel; i++) {
        word[i] = tolower(word[i]);

        if (found_vowel)
            continue;

        /* If VOWELS contains the current character */
        if (strchr(VOWELS, word[i]) != NULL) {
            first_vowel_index = i;
            found_vowel = 1;
        }

        /* Use 'y' as a vowel */
        if (i != 0 && word[i] == 'y') {
            first_vowel_index = i;
            found_vowel = 1;
        }
    }

    int suffixLen = (first_vowel_index == 0) ? 3 : 2;
    char* p_suffix = (first_vowel_index == 0) ? "way" : "ay";

    char* p_result = malloc((word_len + suffixLen) * sizeof(char));
    if (p_result == NULL)
        fprintf(stderr, "Failed to allocate enough memory for the pig latin word!");

    if (first_vowel_index == word_len) {
        fprintf(stderr, "Warning! Consonants only word detected!\n");
        return word;
    }

    /* Copy the from the first vowel onwards to the beginning of the result */
    strcpy(p_result, word + first_vowel_index);
    /* Then append everything that comes before the vowel to the result */
    strncpy(p_result + (word_len - first_vowel_index), word, first_vowel_index);
    /* Finally append the relevant suffix */
    strcpy(p_result + word_len, p_suffix);

    return p_result;
}
