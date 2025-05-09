/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** add_instruction.c
*/

#include "corewar.h"
#include "structures.h"
#include <stdint.h>

int execute_add_instruction(
    UNUSED arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte8_t value = 0;

    if (instruction->param_types[0] == PARAM_REG &&
        instruction->param_types[1] == PARAM_REG &&
        instruction->param_types[2] == PARAM_REG) {
            value = process->registers[instruction->params[0].reg] +
                process->registers[instruction->params[1].reg];
        process->registers[instruction->params[2].reg] = (sbyte4_t)value;
        process->carry = value == 0;
    }
    return 1;
}

int execute_sub_instruction(
    UNUSED arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte8_t value = 0;

    if (instruction->param_types[0] == PARAM_REG &&
        instruction->param_types[1] == PARAM_REG &&
        instruction->param_types[2] == PARAM_REG) {
            value = process->registers[instruction->params[0].reg] -
                process->registers[instruction->params[1].reg];
        process->registers[instruction->params[0].reg] = (sbyte4_t)value;
        process->carry = value == 0;
    }
    return 1;
}
