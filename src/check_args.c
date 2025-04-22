/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** check_args.c
*/

#include "corewar.h"
#include <stdbool.h>
#include <stddef.h>

bool is_usage(
    char *arg,
    corewar_data_t *data)
{
    if (!my_strcmp(arg, USAGE_ARG)) {
        data->usage = true;
        return true;
    }
    return false;
}

bool is_dump(
    char *arg,
    char *arg_next,
    corewar_data_t *data)
{
    char *tmp = NULL;

    if (!my_strcmp(arg, DUMP_ARG) && my_str_isxdigit(arg_next)) {
        data->nbr_cycle = my_strtol(arg_next, &tmp, 16);
        return true;
    }
    return false;
}
