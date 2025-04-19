/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** main.c
*/

#include "corewar.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static bool is_graphical_env(char **env)
{
    for (size_t i = 0; env[i]; i++) {
        if (!my_strncmp(env[i], "DISPLAY", 7))
            return true;
    }
    return false;
}

static corewar_data_t *initialize_data(
    int argc,
    char **argv,
    char **env)
{
    corewar_data_t *data = my_calloc(1, sizeof(corewar_data_t));
    char *tmp;

    for (int i = 1; i < argc; i++) {
        if (!my_strcmp(argv[i], USAGE_ARG)) {
            data->usage = true;
            return data;
        }
        if (!my_strcmp(argv[i], DUMP_ARG) && i + 1 < argc) {
            data->nbr_cycle = my_strtol(argv[i + 1], &tmp, 16);
            i++;
            continue;
        }
        write(STDERR_FILENO, "Incorrect argument\n", 19);
        display_usage();
        return NULL;
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

    if (data->usage) {
        display_usage();
        free_garbage();
        return 0;
    }
    if (!data || !data->nbr_cycle) {
        free_garbage();
        return 84;
    }
    free_garbage();
    return 0;
}
