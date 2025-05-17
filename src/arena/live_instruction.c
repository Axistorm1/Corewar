#include "bonus.h"
#include "corewar.h"
#include "op.h"
#include "structures.h"
#include "arena.h"
#include <stdio.h>

static void write_player_line(robot_info_t *robot, arena_t *arena)
{
    char *line = NULL;

    asprintf(&line, "The player %d(%s) is alive.", robot->prog_num, robot->header->prog_name);
    if (BONUS_MODE == 0) {
        puts(line);
    } else
        update_console_window(line, robot->prog_num, arena->total_cycles);
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

    if (instruction->types[0] == PARAM_DIR)
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
