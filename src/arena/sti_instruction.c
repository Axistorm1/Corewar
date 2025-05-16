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
    instruction_t *instr)
{
    sbyte4_t value = 0;
    sbyte8_t adress = 0;
    sbyte8_t adr2 = 0;

    if (instr->types[0] == PARAM_REG && instr->params[0].reg < REG_NUMBER)
        value = process->registers[instr->params[0].reg];
    else
        return 1;
    adress = get_data_in_param(&(type_and_param_t){instr->types[1],
        instr->params[1]}, ALL_PARAMS, arena, process);
    adr2 = get_data_in_param(&(type_and_param_t){instr->types[2],
        instr->params[2]}, PARAM_DIR | PARAM_REG | PARAM_DIRDEX, arena,
        process);
    if (adress == ERROR_VALUE || adr2 == ERROR_VALUE)
        return 1;
    adress += adr2;
    write4_to_arena(arena, update_program_counter(process->pc, (sbyte2_t)
        (adress % IDX_MOD)), (byte4_t)value, process->robot->prog_num);
    return 1;
}
