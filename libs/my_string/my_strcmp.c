/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** compares str1 and str2
*/

#include "my_string.h"

int my_strcmp(const char *str1, const char *str2)
{
    my_size_t i = 0;

    for (; str1[i] == str2[i]; i++)
        if (str1[i] == '\0')
            return str1[i] - str2[i];
    return str1[i] - str2[i];
}
