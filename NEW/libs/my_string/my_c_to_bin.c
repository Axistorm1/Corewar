/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** transforms a character into a string in binary
** (non-standard)
*/

#include "../my_stdlib/my_stdlib.h"
#include "my_string.h"

char *my_c_to_bin(char c)
{
    char *binary = my_malloc(sizeof(char) * 9);

    for (int i = 0; i < 8; i++) {
        binary[7 - i] = c % 2 + '0';
        c >>= 1;
    }
    binary[8] = '\0';
    return binary;
}
