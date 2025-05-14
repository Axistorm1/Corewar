/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** st_instruction.c
*/

#include "arena.h"
#include "op.h"
#include "structures.h"
#include "utils.h"

int execute_st_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instr)
{
    sbyte4_t value = 0;

    if (instr->types[0] == PARAM_REG && instr->params[0].reg < REG_NUMBER)
        value = process->registers[instr->params[0].reg];
    else
        return 1;
    if (instr->types[1] == PARAM_REG && instr->params[1].reg < REG_NUMBER)
        process->registers[instr->params[1].reg] = value;
    else if (instr->types[1] == PARAM_IND)
        write4_to_arena(arena,
            update_program_counter(process->pc, instr->params[1].index),
            (byte4_t)value, process->robot->prog_num);
    return 1;
}
