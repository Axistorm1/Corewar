#include "my_stdlib.h"

void *my_reallocarray(void *ptr, my_size_t nmemb, my_size_t size)
{
    return my_realloc(ptr, nmemb * size, size);
}
