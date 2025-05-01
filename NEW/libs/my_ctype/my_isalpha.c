/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is alpha
*/

#include "my_ctype.h"

int my_isalpha(char c)
{
    if (my_islower(c) || my_isupper(c))
        return 1;
    return 0;
}
