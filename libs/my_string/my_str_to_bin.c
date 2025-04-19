/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** transforms a string into another string in binary
** (non-standard)
*/

#include "my_string.h"
#include "../my_stdlib/my_stdlib.h"

char *my_str_to_bin(const char *str, my_size_t len)
{
    char *binary = my_malloc(sizeof(char) * len * 8 + 1);
    char *c_bin = MY_NULL;

    for (my_size_t i = 0; i < len; i++) {
        c_bin = my_c_to_bin(str[i]);
        my_memcpy(&binary[i * 8], c_bin, 8);
        my_free(c_bin);
    }
    binary[len * 8] = '\0';
    return binary;
}
