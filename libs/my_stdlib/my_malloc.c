/*
** EPITECH PROJECT, 2025
** my_malloc
** File description:
** Allocate memory
** why is this here
*/

#include "my_stdlib.h"
#include "my_malloc.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void **add_to_garbage_array(
    void **array,
    void *ptr,
    size_t garbage_size)
{
    static size_t array_size = 2;

    if (garbage_size >= array_size - 2) {
        array_size <<= 1;
        array = realloc(array, sizeof(void *) * (array_size + 2));
    }
    array[garbage_size] = ptr;
    array[garbage_size + 1] = NULL;
    return array;
}

static void modify_garbage_ptr(void **array,
    void *old_ptr,
    void *new_ptr,
    size_t garbage_size)
{
    for (size_t i = 0; i < garbage_size; i++)
        if (array[i] == old_ptr) {
            free(old_ptr);
            array[i] = new_ptr;
            break;
        }
}

static void free_garbage_array(
    void **array,
    size_t garbage_size)
{
    for (size_t i = 0; i < garbage_size; i++)
        if (array[i])
            free(array[i]);
    free(array);
}

void collect_garbage(
    void *ptr,
    void *old_ptr,
    int mode)
{
    static size_t garbage_size = 0;
    static void **garbage_array = NULL;

    if (mode == ADD_MODE) {
        garbage_array = add_to_garbage_array(garbage_array, ptr, garbage_size);
        garbage_size++;
    }
    if (mode == MODIF_MODE) {
        modify_garbage_ptr(garbage_array, old_ptr, ptr, garbage_size);
    }
    if (mode == FREE_MODE)
        free_garbage_array(garbage_array, garbage_size);
}

void *my_malloc(my_size_t bytes)
{
    void *ptr = malloc(bytes);

    collect_garbage(ptr, NULL, ADD_MODE);
    return ptr;
}
