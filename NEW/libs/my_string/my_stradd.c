/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** Like strcat but with an allocated string
*/

#include "my_string.h"
#include "../my_stdlib/my_stdlib.h"

char *my_stradd(char **dest_ptr, char const *src)
{
    char *dest = *dest_ptr;
    my_size_t dest_len = my_strlen(dest);
    my_size_t src_len = my_strlen(src);

    dest = my_calloc(dest_len + src_len + 1, sizeof(char));
    my_strcpy(dest, *dest_ptr);
    my_strcat(dest, src);
    my_free(*dest_ptr);
    *dest_ptr = dest;
    return dest;
}
