/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** st_instruction.c
*/

#include "arena.h"
#include "structures.h"
#include "utils.h"

int execute_st_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte4_t value = 0;

    if (instruction->param_types[0] == PARAM_REG)
        value = process->registers[instruction->params[0].reg];
    if (instruction->param_types[1] == PARAM_REG)
        process->registers[instruction->params[1].reg] = value;
    else if (instruction->param_types[1] == PARAM_IND)
        write4_to_arena(arena,
            update_program_counter(process->program_counter,
                instruction->params[1].index),
            (byte4_t)value, process->robot->prog_num);
    return 1;
}
