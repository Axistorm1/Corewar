/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is an uppercase letter
*/

#include "my_ctype.h"
#include "private.h"

int my_isupper(char c)
{
    return (c >= X_UP_CHAR_MIN && c <= UP_CHAR_MAX);
}
