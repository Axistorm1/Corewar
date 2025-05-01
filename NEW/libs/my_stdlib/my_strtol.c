/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** my_strtol
*/

#include "../my_ctype/my_ctype.h"
#include "../my_stdlib/my_stdlib.h"
#include "../my_string/my_string.h"
#include "private.h"

long my_strtol(const char *str, char **endptr, int base)
{
    int sign = 1;
    double result = 0;
    int index = 0;
    int ascii_diff = '0';

    while (str[index] != '\0' && my_isspace(str[index]))
        index++;
    if (str[index] == '-') {
        sign = -1;
        index++;
    }
    while (str[index] != '\0' && my_strchr(&BASE_TABLE_R[36 - base],
        (char)my_tolower(str[index])) != MY_NULL) {
        result *= 10.0 / 10 * base;
        ascii_diff = my_isalpha(str[index]) ? 'Z' - 3 : '0';
        result += my_tolower(str[index]) - ascii_diff;
        index++;
    }
    *endptr = (char *)&str[index];
    return (long)result * sign;
}
