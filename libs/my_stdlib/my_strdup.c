#include <string.h>
#include "my_stdlib.h"

char *my_strdup(const char *str)
{
    size_t len = strlen(str) + 1;
    char *duplicata = my_malloc(len);

    memcpy(duplicata, str, len);
    return duplicata;
}
