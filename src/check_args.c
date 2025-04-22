/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** check_args.c
*/

#include "corewar.h"
#include "errors.h"
#include <stdbool.h>
#include <stddef.h>

static bool is_usage(
    char *arg,
    corewar_data_t *data)
{
    if (!my_strcmp(arg, USAGE_ARG)) {
        data->usage = true;
        return true;
    }
    return false;
}

static bool is_dump(
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

corewar_data_t *check_args(
    int argc,
    char **argv,
    corewar_data_t *data)
{
    for (int i = 1; i < argc; i++) {
        if (is_usage(argv[i], data))
            break;
        if (i + 1 < argc && is_dump(argv[i], argv[i + 1], data)) {
            i++;
            continue;
        }
        return write_error(BAD_ARGUMENT, argv[i], -1);
    }
    return data;
}
