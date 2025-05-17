#include "my_stdlib.h"
#include <string.h>

void *my_calloc(my_size_t nitems, my_size_t size)
{
    void *memory = my_malloc(nitems * size);

    memset(memory, 0, nitems * size);
    return memory;
}
