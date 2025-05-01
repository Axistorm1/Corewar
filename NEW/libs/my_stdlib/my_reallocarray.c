/*
** EPITECH PROJECT, 2025
** my_stdlib
** File description:
** my_reallocarray (non-standard)
*/

#include "my_stdlib.h"

void *my_reallocarray(void *ptr, my_size_t nmemb, my_size_t size)
{
    return my_realloc(ptr, nmemb * size, size);
}
