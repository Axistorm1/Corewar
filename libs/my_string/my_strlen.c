/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** my_strlen
*/

#include "my_string.h"

my_size_t my_strlen(char const *str)
{
    my_size_t count = 0;

    while (str[count] != '\0')
        count++;
    return count;
}
