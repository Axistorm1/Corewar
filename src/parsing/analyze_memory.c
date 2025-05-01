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
    int offset = 1;
    instruction_t *instruction = my_calloc(1, sizeof(instruction_t));

    instruction->op_code = buffer[0];
    instruction->coding_byte = buffer[offset];
    offset += verify_coding_byte(instruction);
    parse_params(instruction, (char *)&buffer[offset]);
    return instruction;
}
