/**
 * Function count_words count the words of a file.
 * Assume that the words are separated by an espace or break lines
 * @param. Pointer to filename (assume just readonly)
 * @return Number of words in a file. Return -1 if error.
**/

#include <stdio.h>

#define MAXWORD 80

int count_words(FILE *file);
