/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** fork_instruction.c
*/

#include "arena.h"
#include "op.h"
#include "structures.h"
#include "utils.h"
#include <stdlib.h>

int execute_fork_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    if (arena->process_count >= (PROCESS_LIMIT - 1))
        return 1;
    if (instruction->types[0] == PARAM_INDEX) {
        instruction->params[0].index %= IDX_MOD;
        return execute_lfork_instruction(arena, process, instruction);
    }
    return 1;
}

int execute_lfork_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    process_data_t *new = NULL;
    sbyte2_t value = 0;

    if (arena->process_count >= (PROCESS_LIMIT - 1))
        return 1;
    if (instruction->types[0] == PARAM_INDEX) {
        arena->processes = realloc(arena->processes,
            sizeof(process_data_t *) * (arena->process_count + 2));
        value = instruction->params[0].index;
        new = create_new_process(process, process->robot);
        new->pc = update_program_counter(new->pc, value);
        new->cycle_born = arena->total_cycles;
        arena->processes[arena->process_count] = new;
        arena->process_count++;
    }
    return 1;
}
