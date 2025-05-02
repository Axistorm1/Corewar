/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** live_instruction.c
*/

#include "structures.h"
#include "utils.h"
#include "my_string.h"
#include <unistd.h>

static void write_player_line(robot_info_t *robot)
{
    write(STDOUT_FILENO, "The player ", 11);
    my_puts_nb(robot->prog_num);
    write(STDOUT_FILENO, "(", 1);
    write(STDOUT_FILENO, robot->header->prog_name,
        my_strlen(robot->header->prog_name));
    write(STDOUT_FILENO, ")is alive.\n", 11);
}

static int find_process(
    process_data_t **processes,
    byte4_t process_count,
    sbyte4_t prog_num)
{
    for (byte4_t i = 0; i < process_count; i++)
        if (processes[i]->robot->prog_num == prog_num) {
            processes[i]->alive = true;
            processes[i]->robot->alive = true;
            write_player_line(processes[i]->robot);
            return 0;
        }
    return 1;
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
        process->alive = true;
        process->robot->alive = true;
        write_player_line(process->robot);
        return 1;
    }
    find_process(arena->processes, arena->process_count, value);
    return 1;
}
