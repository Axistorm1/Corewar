/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** my_div
*/

#include "my_stdlib.h"

my_div_t my_div(int numerator, int denomimator)
{
    return (my_div_t){numerator / denomimator, numerator % denomimator};
}
