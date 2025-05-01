/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is blank
*/

#include "my_ctype.h"
#include "private.h"

int my_isblank(char c)
{
    return (c == TAB || c == SPACE);
}
