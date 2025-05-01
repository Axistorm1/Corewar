/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** returns the length of an array of strings
*/

#include "my_string.h"

my_size_t str_array_len(char **array)
{
    my_size_t len = 0;

    while (array[len])
        len++;
    return len;
}
