/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** returns a string comprised of all letters in lowercase
*/

#include "my_string.h"
#include "../my_ctype/my_ctype.h"

// Modifies original str
char *str_tolower(char *str)
{
    my_size_t len = my_strlen(str);

    for (my_size_t i = 0; i < len; i++)
        str[i] = (char)my_tolower(str[i]);
    return str;
}
