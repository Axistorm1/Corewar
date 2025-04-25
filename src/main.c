/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** main.c
*/

#include "corewar.h"
#include "../include/op.h"
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
    if (!check_args(argc, argv, data))
        return NULL;
    data->graphical_env = is_graphical_env(env);
    return data;
}

int main(
    int argc,
    char **argv,
    char **env)
{
    //corewar_data_t *data = initialize_data(argc, argv, env);
    parsing_data_t parse_data = {0};

    /*if (!data || !data->nbr_cycle) {
        free_garbage();
        return 84;
    }
    if (data->usage) {
        display_usage();
        free_garbage();
        return 0;
    } */
    parse_champions(&parse_data);
    //free_garbage();
    return 0;
}
