/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** my_strndup (non-standard)
*/

#include "my_string.h"
#include "../my_stdlib/my_stdlib.h"

char *my_strndup(const char *str, my_size_t bytes)
{
    char *duplicata = MY_NULL;

    duplicata = my_calloc(1, bytes + 1);
    my_memcpy(duplicata, str, bytes);
    return duplicata;
}
