/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** reverse a string, this is a non standard function
*/

#include "my_string.h"

// Using arithmetic operations to swap variables instead of tmp
char *my_strrev(char *str)
{
    my_size_t len = my_strlen(str) - 1;

    for (my_size_t index = 0; index < len; index++) {
        str[index] = str[index] + str[len];
        str[len] = str[index] - str[len];
        str[index] = str[index] - str[len];
        len--;
    }
    return str;
}
