/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** my_strtok
*/

#include "my_string.h"

char *my_strtok(char *str, const char *delimiters)
{
    static char *current_str;
    char *token = MY_NULL;
    my_size_t token_index = 0;

    if (str != MY_NULL)
        current_str = str;
    if (current_str == MY_NULL)
        return MY_NULL;
    token_index = my_strcspn(current_str, delimiters);
    if (my_strlen(current_str) == 0)
        return MY_NULL;
    current_str[token_index] = '\0';
    token = current_str;
    current_str = &current_str[token_index + 1];
    return token;
}
