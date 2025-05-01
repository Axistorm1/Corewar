/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** Returns a pointer at the index of the last occurence of c in str
*/

#include "my_string.h"

char *my_strchr(const char *str, int c)
{
    for (my_size_t index = 0; str[index] != '\0'; index++)
        if (str[index] == c)
            return (char *)&str[index];
    return MY_NULL;
}
