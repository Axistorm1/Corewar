/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** Returns the length of the longest sub string
** at the start not containing any of str2
*/

#include "my_string.h"

// Using clang makes the ascii_table definition use a memset even with
// the -fno-builtin flag. Solution:
// char ascii_table[256];
// my_memset(ascii_table, 0, 256);
// Or just stop using clang
my_size_t my_strcspn(const char *str1, const char *str2)
{
    char ascii_table[256] = {0};
    my_size_t len1 = my_strlen(str1);
    my_size_t len2 = my_strlen(str2);

    for (my_size_t table_index = 0; table_index < len2; table_index++)
        ascii_table[(int)str2[table_index]] = 1;
    for (my_size_t str_index = 0; str_index < len1; str_index++)
        if (ascii_table[(int)str1[str_index]] != 0)
            return str_index;
    return len1;
}
