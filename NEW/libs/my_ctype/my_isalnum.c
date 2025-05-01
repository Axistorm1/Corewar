/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is alphanumericals
*/

#include "my_ctype.h"

int my_isalnum(char c)
{
    if (my_isalpha(c) || my_isdigit(c))
        return 1;
    return 0;
}
