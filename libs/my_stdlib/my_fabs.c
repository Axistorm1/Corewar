/*
** EPITECH PROJECT, 2025
** my_stdlib
** File description:
** float abs
*/

#include "my_stdlib.h"

double my_fabs(double number)
{
    return number > 0 ? number : -number;
}
