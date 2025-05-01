/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** adds src to dest
*/

#include "my_string.h"

char *my_strcat(char *dest, char const *src)
{
    my_size_t len_dest = my_strlen(dest);
    my_size_t len_src = my_strlen(src);

    for (my_size_t index = 0; index < len_src; index++)
        dest[len_dest + index] = src[index];
    dest[len_dest + len_src] = '\0';
    return dest;
}
