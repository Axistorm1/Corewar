/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** copy from src to dest until bytes is reached
*/

#include "my_string.h"
#include <stdint.h>

void *my_memcpy(void *dest, const void *src, my_size_t bytes)
{
    my_size_t index = 0;

    for (; index < (bytes >> 3); ++index)
        ((uint64_t *)dest)[index] = ((uint64_t *)src)[index];
    index <<= 3;
    for (; index < bytes; index++)
        ((uint8_t *)dest)[index] = ((uint8_t *)src)[index];
    return dest;
}
