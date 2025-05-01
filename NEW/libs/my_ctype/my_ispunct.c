/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is a punctuation
*/

#include "my_ctype.h"
#include "private.h"

int my_ispunct(char c)
{
    if (c >= OPERANDS_MIN && c <= OPERANDS_MAX)
        return 1;
    if (c >= SYMBOLS_MIN && c <= SYMBOLS_MAX)
        return 1;
    if (c >= SYMBOLS2_MIN && c <= SYMBOLS2_MAX)
        return 1;
    if (c >= SYMBOLS3_MIN && c <= SYMBOLS3_MAX)
        return 1;
    return 0;
}
