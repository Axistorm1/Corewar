/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** or_instruction.c
*/

#include "arena.h"
#include "structures.h"
#include "arena.h"

int execute_or_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte8_t first_value = 0;
    sbyte8_t second_value = 0;

    first_value = get_data_in_param(&(type_and_param_t)
        {instruction->param_types[0], instruction->params[0]},
        ALL_PARAMS, arena, process);
    second_value = get_data_in_param(&(type_and_param_t)
        {instruction->param_types[1], instruction->params[1]},
        ALL_PARAMS, arena, process);
    if (first_value == 1L << 32 || second_value == 1L << 32)
        return 1;
    if (instruction->param_types[2] == PARAM_REG) {
        process->registers[instruction->params[2].reg] =
            (sbyte4_t)first_value | (sbyte4_t)second_value;
        process->carry = process->registers[instruction->params[2].reg] == 0;
    }
    return 1;
}

int execute_xor_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte8_t first_value = 0;
    sbyte8_t second_value = 0;

    first_value = get_data_in_param(&(type_and_param_t)
        {instruction->param_types[0], instruction->params[0]},
        ALL_PARAMS, arena, process);
    second_value = get_data_in_param(&(type_and_param_t)
        {instruction->param_types[1], instruction->params[1]},
        ALL_PARAMS, arena, process);
    if (first_value == 1L << 32 || second_value == 1L << 32)
        return 1;
    if (instruction->param_types[2] == PARAM_REG) {
        process->registers[instruction->params[2].reg] =
            (sbyte4_t)first_value ^ (sbyte4_t)second_value;
        process->carry = process->registers[instruction->params[2].reg] == 0;
    }
    return 1;
}
