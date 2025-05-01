/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** copy bytes of src into dest
*/

#include "my_string.h"

char *my_strncpy(char *dest, char const *src, my_size_t bytes)
{
    my_size_t index = 0;

    while (src[index] != '\0' && index < bytes) {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}
