/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** reallocate the desired memory size
*/

#include "my_stdlib.h"
#include "my_malloc.h"
#include "../my_string/my_string.h"
#include <stddef.h>

void *my_realloc(void *ptr, my_size_t size, my_size_t old_size)
{
    void *new_ptr = my_malloc(size);

    my_memcpy(new_ptr, ptr, old_size);
    collect_garbage(NULL, ptr, MODIF_MODE);
    return new_ptr;
}
