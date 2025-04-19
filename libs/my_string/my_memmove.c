/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** move memory from block a to block b
*/

#include "my_string.h"

// Could be WAY better but i'm lazy
// This crashes sometimes, i'll check up on it later once i have a better
// understanding
//
// ---
//
// Couldn't reproduce? Might need to do actual tests...
void *my_memmove(void *dest, const void *src, my_size_t bytes)
{
    unsigned char buffer[bytes];

    my_memcpy(buffer, src, bytes);
    my_memcpy(dest, buffer, bytes);
    return dest;
}
