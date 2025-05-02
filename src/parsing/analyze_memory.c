/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** analyze_memory.c
*/

#include "parsing.h"
#include "structures.h"
#include "my_stdlib.h"

instruction_t *analyze_memory(byte1_t *buffer)
{
    byte1_t offset = 0;
    instruction_t *instruction = my_calloc(1, sizeof(instruction_t));

    instruction->op_code = buffer[0];
    instruction->coding_byte = buffer[1];
    offset += verify_coding_byte(instruction);
    offset += parse_params(instruction, &buffer[offset]);
    instruction->size = offset;
    return instruction;
}
