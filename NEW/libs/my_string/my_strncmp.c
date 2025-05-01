/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** compares str1 and str2 until bytes
*/

#include "my_string.h"

int my_strncmp(char const *str1, char const *str2, my_size_t bytes)
{
    for (my_size_t index = 0; index < bytes; index++)
        if (str1[index] != str2[index])
            return str1[index] - str2[index];
    return 0;
}
