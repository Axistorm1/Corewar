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
#include "bonus.h"
#include "arena.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "game_info.h"
static bool is_graphical_env(char **env)
{
    for (size_t i = 0; env[i]; i++)
        if (!my_strncmp(env[i], "DISPLAY", 7))
            return true;
    return false;
}

static corewar_data_t *initialize_data(
    int argc,
    const char **argv)
{
    corewar_data_t *data = my_calloc(1, sizeof(corewar_data_t));

    data->dump_cycle = (byte4_t)-1;
    data->robots = my_calloc((my_size_t)argc, sizeof(robot_info_t *));
    if (!check_args(argc, argv, data))
        return NULL;
    return data;
}

static byte2_t find_lowest_prog_num(
    robot_info_t **robots,
    byte4_t robot_count)
{
    byte2_t lowest = 1;

    for (byte2_t i = 0; i < robot_count; i++) {
        if (robots[i]->prog_num == lowest) {
            lowest++;
            i = (byte2_t)-1;
        }
    }
    return lowest;
}

static void assign_default_values(corewar_data_t *data)
{
    for (byte2_t i = 0; i < data->robot_count; i++)
        if (data->robots[i]->prog_num == (byte2_t)-1)
            data->robots[i]->prog_num =
                find_lowest_prog_num(data->robots, data->robot_count);
}

int main(
    int argc,
    const char **argv,
    char **env)
{
    corewar_data_t *data = initialize_data(argc, argv);
    game_info game_data = {0};

    if (BONUS_MODE == 1) {
        if (my_menu(&game_data) == 0)
            return 0;
        setup_audio(&game_data);
    }
    if (!data || (BONUS_MODE == 1 && !is_graphical_env(env))) {
        free_garbage();
        return 84;
    }
    if (data->usage) {
        display_usage();
        free_garbage();
        return 0;
    }
    assign_default_values(data);
    distribute_robots(data->robots, data->robot_count);
    if (BONUS_MODE == 1)
        launch_ncurses();
    create_arena(data);
    free_garbage();
    if (BONUS_MODE == 1)
        exit_ncurses();
    return 0;
}
