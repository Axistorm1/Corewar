/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Returns a lowercase character corresponding to the uppercase character
*/

#include "my_ctype.h"
#include "private.h"

int my_tolower(char c)
{
    if (my_isupper(c))
        return c + UPPER_TO_LOWER_DIFF;
    return c;
}
