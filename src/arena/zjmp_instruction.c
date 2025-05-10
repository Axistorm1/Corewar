/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** zjmp_instruction.c
*/

#include "corewar.h"
#include "op.h"
#include "structures.h"
#include "utils.h"
#include "arena.h"

int execute_zjmp_instruction(
    UNUSED arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte4_t value = 0;

    if (!process->carry)
        return 1;
    if (instruction->param_types[0] == PARAM_DIRDEX)
        value = instruction->params[0].index;
    process->pc = update_program_counter(process->pc,
        (sbyte2_t)(value % IDX_MOD));
    return 0;
}
