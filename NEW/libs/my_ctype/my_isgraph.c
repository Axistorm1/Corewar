/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character has a graphical representation
*/

#include "my_ctype.h"
#include "private.h"

int my_isgraph(char c)
{
    return (c >= OPERANDS_MIN && c <= SYMBOLS3_MAX);
}
