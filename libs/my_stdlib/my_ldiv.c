/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** my_div
*/

#include "my_stdlib.h"

my_ldiv_t my_ldiv(long numerator, long denominator)
{
    return (my_ldiv_t){numerator / denominator, numerator % denominator};
}
