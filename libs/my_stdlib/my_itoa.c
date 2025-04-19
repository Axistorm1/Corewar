/*
** EPITECH PROJECT, 2025
** my_stdlib
** File description:
** int to str (non-standard)
*/

#include "my_stdlib.h"

char *my_itoa(int value, char *str, int base)
{
    return my_ltoa((long)value, str, base);
}
