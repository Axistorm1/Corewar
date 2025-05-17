#include "parsing.h"
#include "structures.h"
#include <stdlib.h>

instruction_t *analyze_memory(byte1_t *buffer)
{
    byte1_t        offset      = 0;
    instruction_t *instruction = calloc(1, sizeof(instruction_t));

    instruction->op_code     = buffer[0];
    instruction->coding_byte = buffer[1];
    offset += (byte1_t)verify_coding_byte(instruction);
    offset += (byte1_t)parse_params(instruction, &buffer[offset]);
    instruction->size = offset;
    return instruction;
}
