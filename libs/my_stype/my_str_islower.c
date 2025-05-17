#include "my_stype.h"
#include <ctype.h>
#include <string.h>

int my_str_islower(char *str)
{
    my_size_t len = strlen(str);

    if (len == 0)
        return 0;
    for (my_size_t i = 0; i < len; i++)
        if (!islower(str[i]))
            return 0;
    return 1;
}
