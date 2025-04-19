/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** my_strdup (non-standard)
*/

#include "my_string.h"
#include "../my_stdlib/my_stdlib.h"

char *my_strdup(const char *str)
{
    my_size_t len = my_strlen(str) + 1;
    char *duplicata = my_malloc(len);

    my_memcpy(duplicata, str, len);
    return duplicata;
}
