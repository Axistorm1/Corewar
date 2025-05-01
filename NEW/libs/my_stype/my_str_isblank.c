/*
** EPITECH PROJECT, 2025
** my_stype
** File description:
** Checks if a string is blank
*/

#include "my_stype.h"
#include "../my_ctype/my_ctype.h"
#include "../my_string/my_string.h"

int my_str_isblank(char *str)
{
    my_size_t len = my_strlen(str);

    if (len == 0)
        return 0;
    for (my_size_t i = 0; i < len; i++)
        if (!my_isblank(str[i]))
            return 0;
    return 1;
}
