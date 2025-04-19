/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** Returns the last occurence of c in str
*/

#include "my_string.h"

char *my_strrchr(const char *str, int c)
{
    char *ptr = MY_NULL;

    for (my_size_t index = 0; str[index] != '\0'; index++)
        if (str[index] == c)
            ptr = (char *)&str[index];
    return ptr;
}
