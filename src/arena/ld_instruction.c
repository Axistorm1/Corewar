/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** ld_instruction.c
*/

#include "arena.h"
#include "op.h"
#include "structures.h"

int execute_ld_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    if (instruction->types[0] == PARAM_IND)
        instruction->params[0].ind %= IDX_MOD;
    if (instruction->types[0] == PARAM_INDEX)
        instruction->params[0].index %= IDX_MOD;
    return execute_lld_instruction(arena, process, instruction);
}

int execute_lld_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instr)
{
    sbyte8_t value = 0;

    value = get_data_in_param(&(type_and_param_t)
        {instr->types[0], instr->params[0]},
        PARAM_DIR | PARAM_IND, arena, process);
    if (value == 1l << 32)
        return 1;
    if (instr->types[1] == PARAM_REG && instr->params[1].reg < REG_NUMBER) {
        process->registers[instr->params[1].reg] = (sbyte4_t)value;
        process->carry = value == 0;
    }
    return 1;
}
