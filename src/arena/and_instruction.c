#include "op.h"
#include "structures.h"
#include "arena.h"

int execute_and_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instr)
{
    sbyte8_t first_value = 0;
    sbyte8_t second_value = 0;

    first_value = get_data_in_param(&(type_and_param_t){instr->types[0],
        instr->params[0]}, ALL_PARAMS, arena, process);
    second_value = get_data_in_param(&(type_and_param_t){instr->types[1],
        instr->params[1]}, ALL_PARAMS, arena, process);
    if (first_value == ERROR_VALUE || second_value == ERROR_VALUE)
        return 1;
    if (instr->types[2] == PARAM_REG && instr->params[2].reg < REG_NUMBER) {
        process->registers[instr->params[2].reg] =
            (sbyte4_t)first_value & (sbyte4_t)second_value;
        process->carry = process->registers[instr->params[2].reg] == 0;
    }
    return 1;
}
