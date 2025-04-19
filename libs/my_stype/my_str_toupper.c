/*
** EPITECH PROJECT, 2025
** my_stype
** File description:
** Returns a lowered case string
*/

#include "my_stype.h"
#include "../my_ctype/my_ctype.h"
#include "../my_string/my_string.h"
#include "private.h"

char *my_str_toupper(char *str)
{
    my_size_t len = my_strlen(str);

    if (len == 0)
        return 0;
    for (my_size_t i = 0; i < len; i++)
        if (my_islower(str[i]))
            str[i] -= UPPER_TO_LOWER_DIFF;
    return str;
}
