/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is printable
*/

#include "my_ctype.h"
#include "private.h"

int my_isprint(char c)
{
    return (c >= SPACE && c <= SYMBOLS3_MAX);
}
