/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** compares str1 and str2 ignoring case
*/

#include "my_string.h"
#include "../my_ctype/my_ctype.h"

int my_strcasecmp(const char *str1, const char *str2)
{
    my_size_t i = 0;

    for (; my_tolower(str1[i]) == my_tolower(str2[i]); i++) {
        if (str1[i] == '\0')
            return my_tolower(str1[i]) - my_tolower(str2[i]);
    }
    return my_tolower(str1[i]) - my_tolower(str2[i]);
}
