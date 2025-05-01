/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** my_atof
*/

#include "my_stdlib.h"

double my_atof(char const *str)
{
    char *endptr = "";

    return (double)my_strtod(str, &endptr);
}
