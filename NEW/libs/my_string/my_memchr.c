/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** Returns a pointer at the index of the first occurence of c in mem
*/

#include "my_string.h"

void *my_memchr(const void *mem, int c, my_size_t n)
{
    my_size_t index = 0;

    while (index < n) {
        if (((const unsigned char *)mem)[index] == c)
            return (void *)&((unsigned char *)mem)[index];
        index++;
    }
    return MY_NULL;
}
