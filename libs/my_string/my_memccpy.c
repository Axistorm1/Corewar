/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** copy from src to dest until c is found or n is reached
*/

#include "my_string.h"

void *my_memccpy(void *dest, const void *src, int c, my_size_t n)
{
    my_size_t index = 0;

    while (index < n) {
        if (((unsigned char *)src)[index] == c)
            return my_memcpy(dest, src, index + 1);
        index++;
    }
    return MY_NULL;
}
