/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** my_atoi
*/

#include "my_stdlib.h"

int my_atoi(char const *str)
{
    char *endptr = "";

    return (int)my_strtol(str, &endptr, 10);
}
