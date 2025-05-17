#include "my_stdlib.h"
#include "my_malloc.h"
#include <stddef.h>
#include <string.h>

void *my_realloc(void *ptr, my_size_t size, my_size_t old_size)
{
    void *new_ptr = my_malloc(size);

    memcpy(new_ptr, ptr, old_size);
    collect_garbage(NULL, ptr, MODIF_MODE);
    return new_ptr;
}
