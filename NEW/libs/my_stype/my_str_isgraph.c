/*
** EPITECH PROJECT, 2025
** my_stype
** File description:
** Checks if a string has a graphical representation
*/

#include "my_stype.h"
#include "../my_ctype/my_ctype.h"
#include "../my_string/my_string.h"

int my_str_isgraph(char *str)
{
    my_size_t len = my_strlen(str);

    if (len == 0)
        return 0;
    for (my_size_t i = 0; i < len; i++)
        if (!my_isgraph(str[i]))
            return 0;
    return 1;
}
