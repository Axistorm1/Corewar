/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** copy a string from src into dest
*/

#include "my_string.h"

char *my_strcpy(char *dest, char const *src)
{
    int index = 0;

    while (src[index] != '\0') {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}
