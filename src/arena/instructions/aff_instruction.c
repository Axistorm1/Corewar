#include "arena.h"
#include "corewar.h"
#include "op.h"
#include "structures.h"
#include <unistd.h>

// do not add a \n
int execute_aff_instruction(UNUSED arena_t *arena, process_data_t *process,
                            instruction_t *instr)
{
    sbyte4_t value = 0;
    char     ascii = 0;

    if (instr->types[0] == PARAM_REG && instr->params[0].reg < REG_NUMBER)
    {
        value = process->registers[instr->params[0].reg] % ASCII_SIZE;
        ascii = (char)value;
        write(STDOUT_FILENO, &ascii, 1);
    }
    return 1;
}
