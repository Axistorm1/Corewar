/*
** EPITECH PROJECT, 2024
** my_stdlib
** File description:
** my_strtod
*/

#include "../my_ctype/my_ctype.h"
#include "../my_string/my_string.h"
#include "my_stdlib.h"

static const char digits[11] = "0123456789\0";

// I see some divisions here, could be optimized by using multiplications
// Too lazy to do it now
double my_strtod(const char *str, char **endptr)
{
    int sign = 1;
    int index = 0;
    double value = 0;
    long tmp_float_l = my_strtol(&my_strpbrk(str, ".")[1], endptr, 10);
    double tmp_float = (double)tmp_float_l;
    double floating_size = 10.0;

    while (str[index] != '\0' && my_isspace(str[index]))
        index++;
    if (str[index] == '-') {
        sign = -1;
        index++;
    }
    while (str[index] != '\0' && my_strchr(digits, str[index]) != MY_NULL) {
        value = value * 10 + str[index] - '0';
        index++;
    }
    while (tmp_float / floating_size > 1)
        floating_size *= 10.0;
    return (value + (tmp_float / floating_size)) * sign;
}
