/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is alpha
*/

#include "my_stype.h"
#include "../my_ctype/my_ctype.h"
#include "../my_string/my_string.h"

int my_str_isalpha(char *str)
{
    my_size_t len = my_strlen(str);

    if (len == 0)
        return 0;
    for (my_size_t i = 0; i < len; i++)
        if (!my_islower(str[i]) && !my_isupper(str[i]))
            return 0;
    return 1;
}
