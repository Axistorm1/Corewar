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

int execute_zjmp_instruction(
    UNUSED arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte4_t value = 0;

    //reverse this once carry works
    if (process->carry)
        return 1;
    if (instruction->param_types[0] == PARAM_DIRDEX)
        value = instruction->params[0].dir;
    process->pc = update_program_counter(process->pc, value % IDX_MOD);
    return 0;
}
