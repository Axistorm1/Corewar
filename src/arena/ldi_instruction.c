/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** ldi_instruction.c
*/

#include "op.h"
#include "arena.h"
#include "structures.h"

int execute_ldi_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    if (instruction->param_types[0] == PARAM_INDEX)
        instruction->params[0].index %= IDX_MOD;
    if (instruction->param_types[0] == PARAM_IND)
        instruction->params[0].ind %= IDX_MOD;
    return execute_lldi_instruction(arena, process, instruction);
}

int execute_lldi_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte8_t adress = 0;
    sbyte8_t sum = 0;
    sbyte8_t tmp = 0;
    sbyte4_t value = 0;

    adress = get_data_in_param(&(type_and_param_t){instruction->param_types[0],
        instruction->params[0]}, ALL_PARAMS, arena, process);
    tmp = get_data_in_param(&(type_and_param_t){instruction->param_types[1],
        instruction->params[1]}, PARAM_REG | PARAM_DIR | PARAM_DIRDEX,
        arena, process);
    if (adress == 1l << 32 || tmp == 1l << 32)
        return 1;
    sum = arena->memory[process->pc + (adress)];
    sum += tmp;
    value = arena->memory[process->pc + (sum)];
    if (instruction->param_types[2] == PARAM_REG) {
        process->registers[instruction->params[2].reg] = value;
        process->carry = value == 0;
    }
    return 1;
}
