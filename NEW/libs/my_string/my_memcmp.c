/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** Compare two blocks of memory
*/

#include "my_string.h"
#include <stdint.h>

int my_memcmp(
    const void *str1, const void *str2, my_size_t bytes)
{
    while (bytes > 0 &&
        ((uint8_t *)str1)[bytes - 1] == ((uint8_t *)str2)[bytes - 1])
        bytes--;
    if (bytes == 0)
        return 0;
    if (((uint8_t *)str1)[bytes] > ((uint8_t *)str2)[bytes])
        return 1;
    return -1;
}
