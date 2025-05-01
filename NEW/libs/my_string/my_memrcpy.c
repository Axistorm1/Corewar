/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** copy from src to dest starting from the end until bytes is reached
** memory reverse copy
*/

#include "my_string.h"
#include <stdint.h>

// I have never heard of aligning in my life
void *my_memrcpy(void *dest, const void *src, my_size_t bytes)
{
    my_size_t index = 0;

    for (; index < (bytes >> 3); index++)
        ((uint64_t *)dest)[bytes - index - 1] = ((uint64_t *)src)[index];
    index <<= 3;
    for (; index < bytes; index++)
        ((uint8_t *)dest)[bytes - index - 1] = ((uint8_t *)src)[index];
    return dest;
}
