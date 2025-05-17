#include "arena.h"
#include "corewar.h"
#include "op.h"
#include "structures.h"
#include <stdint.h>

int execute_add_instruction(
    UNUSED arena_t *arena,
    process_data_t *process,
    instruction_t *instr)
{
    sbyte8_t value = 0;

    if (instr->types[0] == PARAM_REG && instr->params[0].reg < REG_NUMBER &&
        instr->types[1] == PARAM_REG && instr->params[1].reg < REG_NUMBER &&
        instr->types[2] == PARAM_REG && instr->params[2].reg < REG_NUMBER) {
            value = process->registers[instr->params[0].reg] +
                process->registers[instr->params[1].reg];
            process->registers[instr->params[2].reg] = (sbyte4_t)value;
        process->carry = value == 0;
    }
    return 1;
}

int execute_sub_instruction(
    UNUSED arena_t *arena,
    process_data_t *process,
    instruction_t *instr)
{
    sbyte8_t value = 0;

    if (instr->types[0] == PARAM_REG && instr->params[0].reg < REG_NUMBER &&
        instr->types[1] == PARAM_REG && instr->params[1].reg < REG_NUMBER &&
        instr->types[2] == PARAM_REG && instr->params[2].reg < REG_NUMBER) {
            value = process->registers[instr->params[0].reg] -
                process->registers[instr->params[1].reg];
        process->registers[instr->params[0].reg] = (sbyte4_t)value;
        process->carry = value == 0;
    }
    return 1;
}
