/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Returns an uppercase character corresponding to the lowercase character
*/

#include "my_ctype.h"
#include "private.h"

int my_toupper(char c)
{
    if (my_islower(c))
        return c - UPPER_TO_LOWER_DIFF;
    return c;
}
