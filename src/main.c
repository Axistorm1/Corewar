/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** main.c
*/

#include "corewar.h"
#include "errors.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static bool is_graphical_env(char **env)
{
    for (size_t i = 0; env[i]; i++)
        if (!my_strncmp(env[i], "DISPLAY", 7))
            return true;
    return false;
}

static corewar_data_t *initialize_data(
    int argc,
    char **argv,
    char **env)
{
    corewar_data_t *data = my_calloc(1, sizeof(corewar_data_t));

    data->nbr_cycle = 1;
    for (int i = 1; i < argc; i++) {
        if (is_usage(argv[i], data))
            break;
        if (i + 1 < argc && is_dump(argv[i], argv[i + 1], data)) {
            i++;
            continue;
        }
        return write_error(BAD_ARGUMENT, argv[i], -1);
    }
    data->graphical_env = is_graphical_env(env);
    return data;
}

int main(
    int argc,
    char **argv,
    char **env)
{
    corewar_data_t *data = initialize_data(argc, argv, env);

    if (!data || !data->nbr_cycle) {
        free_garbage();
        return 84;
    }
    if (data->usage) {
        display_usage();
        free_garbage();
        return 0;
    }
    free_garbage();
    return 0;
}
