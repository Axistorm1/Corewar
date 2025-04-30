/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** main.c
*/

#include "corewar.h"
#include "parsing.h"
#include "structures.h"
#include <stddef.h>
#include <stdint.h>
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
    const char **argv,
    char **env)
{
    corewar_data_t *data = my_calloc(1, sizeof(corewar_data_t));

    data->nbr_cycle = -1;
    data->programs = my_calloc((my_size_t)argc, sizeof(program_data_t *));
    if (!check_args(argc, argv, data))
        return NULL;
    data->graphical_env = is_graphical_env(env);
    return data;
}

static corewar_data_t *load_instructions(corewar_data_t *data)
{
    for (uint8_t i = 0; i < data->robot_count; i++) {
        data->programs[i]->data = my_calloc(1, sizeof(parsing_data_t));
        parse_champions(data->programs[i]->data, data->programs[i]);
    }
    return data;
}

int main(
    int argc,
    const char **argv,
    char **env)
{
    corewar_data_t *data = initialize_data(argc, argv, env);

    if (!data) {
        free_garbage();
        return 84;
    }
    if (data->usage) {
        display_usage();
        free_garbage();
        return 0;
    }
    load_instructions(data);
    run_arena(data);
    free_garbage();
    return 0;
}
