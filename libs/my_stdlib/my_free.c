#include "my_stdlib.h"
#include "my_malloc.h"
#include <stdlib.h>

void free_garbage(void)
{
    collect_garbage(NULL, NULL, FREE_MODE);
}

void my_free(void *ptr)
{
    free(ptr);
}
