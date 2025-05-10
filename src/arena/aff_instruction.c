/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** aff_instruction.c
*/

#include "arena.h"
#include "structures.h"
#include "corewar.h"
#include <unistd.h>

// do not add a \n
int execute_aff_instruction(
    UNUSED arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte4_t value = 0;
    char ascii = 0;

    if (instruction->param_types[0] == PARAM_REG) {
        value = process->registers[instruction->params[0].reg] % 256;
        ascii = (char)value;
        write(STDOUT_FILENO, &ascii, 1);
        return 1;
    }
    return 1;
}
