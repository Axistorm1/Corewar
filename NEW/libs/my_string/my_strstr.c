/*
** EPITECH PROJECT, 2024
** my_string
** File description:
** Returns the position of needle in haystack if any is found
** Uses the Boyer-Moore-Horspool algorithm
** https://en.wikipedia.org/wiki/Boyer-Moore-Horspool_algorithm
*/

#include "my_string.h"

char *my_strstr(const char *haystack, const char *needle)
{
    my_size_t needle_len = my_strlen(needle);
    my_size_t haystack_len = my_strlen(haystack);
    my_size_t skip_table[256] = {0};
    my_size_t skip_amount = 0;

    if (my_memcmp(needle, "", 1) == 0)
        return (char *)haystack;
    for (my_size_t table_index = 0; table_index < 255; table_index++)
        skip_table[table_index] = needle_len;
    for (my_size_t str_index = 0; str_index < needle_len - 1; str_index++)
        skip_table[(int)needle[str_index]] = needle_len - 1 - str_index;
    while (haystack_len - skip_amount >= needle_len) {
        if (my_memcmp(&haystack[skip_amount], needle, needle_len) == 0)
            return (char *)&haystack[skip_amount];
        skip_amount += skip_table[(int)haystack[skip_amount + needle_len - 1]];
    }
    return MY_NULL;
}
