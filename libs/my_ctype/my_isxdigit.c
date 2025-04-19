/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is an hexadecimal digit
*/

#include "my_ctype.h"
#include "private.h"

int my_isxdigit(char c)
{
    if (c >= DIGITS_MIN && c <= DIGITS_MAX)
        return 1;
    if (c >= X_UP_CHAR_MIN && c <= X_UP_CHAR_MAX)
        return 1;
    if (c >= X_LOW_CHAR_MIN && c <= X_LOW_CHAR_MAX)
        return 1;
    return 0;
}
