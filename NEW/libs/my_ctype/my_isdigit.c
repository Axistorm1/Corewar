/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is a digit
*/

#include "my_ctype.h"
#include "private.h"

int my_isdigit(char c)
{
    return (c >= DIGITS_MIN && c <= DIGITS_MAX);
}
