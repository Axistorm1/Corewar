/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** Finds the first occurence of any char of str2 in str1
*/

#include "my_string.h"

char *my_strpbrk(const char *str1, const char *str2)
{
    my_size_t result = my_strcspn(str1, str2);

    if (result == my_strlen(str1))
        return MY_NULL;
    return (char *)&str1[result];
}
