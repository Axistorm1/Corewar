/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is a lowercase letter
*/

#include "my_ctype.h"
#include "private.h"

int my_islower(char c)
{
    return (c >= X_LOW_CHAR_MIN && c <= LOW_CHAR_MAX);
}
