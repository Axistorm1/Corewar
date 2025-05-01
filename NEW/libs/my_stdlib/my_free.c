/*
** EPITECH PROJECT, 2025
** my_malloc
** File description:
** Free a pseudo-allocated memory block
** Only works with my_malloc allocated blocks
** Currently returning maximal values on error, probably shouldn't
*/

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
