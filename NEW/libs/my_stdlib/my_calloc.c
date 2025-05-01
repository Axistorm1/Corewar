/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** return a memory block with all bytes set to 0
*/

#include "my_stdlib.h"
#include "../my_string/my_string.h"

void *my_calloc(my_size_t nitems, my_size_t size)
{
    void *memory = my_malloc(nitems * size);

    my_memset(memory, 0, nitems * size);
    return memory;
}
