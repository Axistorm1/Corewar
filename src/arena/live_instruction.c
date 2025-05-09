/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** live_instruction.c
*/

#include "bonus.h"
#include "corewar.h"
#include "op.h"
#include "structures.h"
#include "my_stdlib.h"
#include "my_string.h"
#include <unistd.h>

static void write_player_line(robot_info_t *robot, arena_t *arena)
{
    char player_line[200];

    my_memset(player_line, 0, 200);
    my_strcat(player_line, "The player ");
    my_itoa(robot->prog_num, &player_line[11], 10);
    my_strcat(player_line, "(");
    my_strcat(player_line, robot->header->prog_name);
    my_strcat(player_line, ")is alive.\n");
    if (BONUS_MODE == 0) {
        write(STDOUT_FILENO, player_line, my_strlen(player_line));
        return;
    }
    if (BONUS_MODE == 1)
        update_console_window(
            player_line, robot->prog_num, arena->total_cycles);
}

static void handle_alive(process_data_t *process, arena_t *arena)
{
    process->alive = true;
    process->robot->alive = true;
    if (arena->nbr_live < NBR_LIVE)
        arena->nbr_live++;
    write_player_line(process->robot, arena);
}

static bool find_process(
    process_data_t **processes,
    byte4_t process_count,
    sbyte4_t prog_num,
    arena_t *arena)
{
    for (byte4_t i = 0; i < process_count; i++)
        if (processes[i]->robot->prog_num == prog_num) {
            handle_alive(processes[i], arena);
            return true;
        }
    return false;
}

int execute_live_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte4_t value = 0;

    if (instruction->param_types[0] == PARAM_DIR)
        value = instruction->params[0].dir;
    else
        return 1;
    if (process->robot->prog_num == value) {
        handle_alive(process, arena);
        return 1;
    }
    if (!find_process(arena->processes, arena->process_count, value, arena))
        return 1;
    return 1;
}
