/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** my_atol
*/

#include "my_stdlib.h"

long my_atol(char const *str)
{
    char *endptr = "";

    return (long)my_strtol(str, &endptr, 10);
}
