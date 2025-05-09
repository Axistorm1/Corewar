/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** sti_instruction.c
*/

#include "arena.h"
#include "op.h"
#include "structures.h"
#include "utils.h"
#include <stdint.h>

int execute_sti_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte4_t value = 0;
    sbyte8_t adress = 0;

    if (instruction->param_types[0] == PARAM_REG)
        value = process->registers[instruction->params[0].reg];
    adress = get_data_in_param(&(type_and_param_t){instruction->param_types[1],
        instruction->params[1]}, ALL_PARAMS, arena, process);
    if (adress == 1l << 32)
        return 1;
    if (instruction->param_types[2] == PARAM_DIR)
        adress += instruction->params[2].dir;
    if (instruction->param_types[2] == PARAM_REG)
        adress += process->registers[instruction->params[2].reg];
    write4_to_arena(arena, update_program_counter(process->pc, (sbyte2_t)
        (adress % IDX_MOD)) + 1, (byte4_t)value, process->robot->prog_num);
    return 1;
}
