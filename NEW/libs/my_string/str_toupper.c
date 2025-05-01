/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** returns a string comprised of all letters in uppercase
*/

#include "my_string.h"
#include "../my_ctype/my_ctype.h"

// Modifies original str
char *str_toupper(char *str)
{
    my_size_t len = my_strlen(str);

    for (my_size_t i = 0; i < len; i++)
        str[i] = (char)my_toupper(str[i]);
    return str;
}
