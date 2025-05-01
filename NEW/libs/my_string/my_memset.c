/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** copies c into str
*/

#include "my_string.h"

// Seeing some issues with some strings not correctly initialized but...
// not my business
//
// ---
//
// what am i even babbling about?
void *my_memset(void *str, int c, my_size_t bytes)
{
    char *ptr = (char *)str;

    for (my_size_t index = 0; index < bytes; index++)
        ptr[index] = (char)c;
    return str;
}
