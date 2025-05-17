#include <string.h>
#include "utils.h"

size_t str_array_len(char **array)
{
    size_t len = 0;

    while (array[len])
        len++;
    return len;
}
