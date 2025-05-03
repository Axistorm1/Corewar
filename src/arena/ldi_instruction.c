/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** ldi_instruction.c
*/

#include "op.h"
#include "structures.h"

/* takes 3 parameters. The first two must be indexes or registers, the third one
must be a register. This operation modifies the carry. ldi 3, %4, r1 reads
IND_SIZE bytes from the address PC + 3 % IDX_MOD, adds 4 to this value. The sum is
named S. REG_SIZE bytes are read from the address PC + S % IDX_MOD and copied
into r1 */

int execute_ldi_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
}

int execute_lldi_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte4_t adress = 0;
    sbyte8_t sum = 0;
    sbyte4_t value = 0;

    if (instruction->param_types[0] == PARAM_REG)
        adress = process->registers[instruction->params[0].reg];
    if (instruction->param_types[0] == PARAM_DIR)
        adress = instruction->params[0].dir;
    if (instruction->param_types[0] == PARAM_IND)
        adress = arena->memory[process->pc + instruction->params[0].ind];
    if (instruction->param_types[0] == PARAM_DIRDEX)
        adress = instruction->params[0].index;
    if (instruction->param_types[0] == PARAM_INDEX)
        adress = arena->memory[process->pc + instruction->params[0].index];
    sum = arena->memory[process->pc + (adress)];
    if (instruction->param_types[1] == PARAM_REG)
        sum += process->registers[instruction->params[1].reg];
    if (instruction->param_types[1] == PARAM_DIR)
        sum += instruction->params[1].dir;
    if (instruction->param_types[1] == PARAM_DIRDEX)
        sum += instruction->params[1].index;
    value = arena->memory[process->pc + (sum)];
    if (instruction->param_types[2] == PARAM_REG)
        process->registers[instruction->params[2].reg] = value;
    return 1;
}
