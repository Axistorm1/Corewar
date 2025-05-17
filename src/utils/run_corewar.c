#include "corewar.h"
#include "structures.h"
#include "my_stdlib.h"
#include "utils.h"
#include "bonus.h"
#include "arena.h"
#include "game_info.h"
#include <stddef.h>
#include <string.h>
#include <unistd.h>


static bool is_graphical_env(char **env)
{
    if (BONUS_MODE == 1)
        return isatty(STDOUT_FILENO);
    for (size_t i = 0; env[i]; i++)
        if (!strncmp(env[i], "DISPLAY", 7))
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
    byte4_t robot_count,
    bool *found)
{
    for (byte2_t i = 0; i < robot_count; i++)
        if (found[i] == false) {
            found[i] = true;
            return i + 1;
        }
    return 0;
}

static void assign_default_values(corewar_data_t *data)
{
    bool *found = my_calloc(data->robot_count, sizeof(bool));

    for (byte2_t i = 0; i < data->robot_count; i++)
        if (data->robots[i]->prog_num != (byte2_t)-1 &&
            data->robots[i]->prog_num < data->robot_count)
            found[data->robots[i]->prog_num] = true;
    for (byte2_t i = 0; i < data->robot_count; i++)
        if (data->robots[i]->prog_num == (byte2_t)-1)
            data->robots[i]->prog_num =
                find_lowest_prog_num(data->robot_count, found);
}

static int handle_usage(void)
{
    display_usage();
    free_garbage();
    return 0;
}

static int handle_program(
    corewar_data_t *data,
    game_info_t *game_data)
{
    assign_default_values(data);
    if (!distribute_robots(data->robots, data->robot_count))
        return EXIT_ERROR;
    if (BONUS_MODE == 1)
        launch_ncurses(game_data);
    create_arena(data);
    free_garbage();
    if (BONUS_MODE == 1)
        exit_ncurses();
    return 0;
}

// this function is a copy of main, only used for tests
int run_corewar(int argc, const char **argv, char **env)
{
    corewar_data_t *data = initialize_data(argc, argv);
    game_info_t game_data = {0};

    if (!data || (BONUS_MODE == 1 && !is_graphical_env(env))) {
        free_garbage();
        return EXIT_ERROR;
    }
    if (data->usage)
        return handle_usage();
    if (BONUS_MODE == 1) {
        if (my_menu(&game_data) == 0)
            return 0;
        setup_audio(&game_data);
        add_raylib_champions(data, &game_data);
    }
    return handle_program(data, &game_data);
}
