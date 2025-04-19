/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** returns an array of pointers to words
** (delimiters are all non-printable + punct + operators)
** Modifies the original string by changing delimiters by 0s
** (non-standard)
*/

#include "my_string.h"
#include <string.h>
#include "../my_stdlib/my_stdlib.h"

static const char *const default_delimiters =
" !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

// Returns a null-terminated allocated array of pointers to words
// A word is an alphanumerical suite of characters
// Modifies the original string
// If multiple delimiters follow each other, they will be skipped
char **str_to_word_array(char *str, char *delimiters)
{
    char **array = my_malloc(sizeof(char *));
    char *words = MY_NULL;
    my_size_t index = 0;

    if (!delimiters)
        delimiters = (char *)default_delimiters;
    words = strtok(str, delimiters);
    for (; words; index++) {
        array[index] = my_strdup(words);
        words = strtok(MY_NULL, delimiters);
        array = my_reallocarray(array, index + 2, sizeof(char *));
    }
    array[index] = MY_NULL;
    return array;
}
