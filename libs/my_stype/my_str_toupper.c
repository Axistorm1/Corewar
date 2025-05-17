#include "my_stype.h"
#include "private.h"
#include <ctype.h>
#include <string.h>

char *my_str_toupper(char *str)
{
    my_size_t len = strlen(str);

    if (len == 0)
        return 0;
    for (my_size_t i = 0; i < len; i++)
        if (islower(str[i]))
            str[i] -= UPPER_TO_LOWER_DIFF;
    return str;
}
