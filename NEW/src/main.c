/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** main.c
*/

#include "corewar.h"
#include "structures.h"
#include "my_string.h"
#include "my_stdlib.h"
#include "utils.h"
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

    data->dump_cycle = MAX_CYCLES + 1;
    data->robots = my_calloc((my_size_t)argc, sizeof(robot_info_t *));
    if (!check_args(argc, argv, data))
        return NULL;
    data->grapical_env = is_graphical_env(env);
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
    //print_programs_data(data->programs, data->robot_count);
    //load_arena(data);
    free_garbage();
    return 0;
}
