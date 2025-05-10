/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** not_instruction.c
*/

#include "corewar.h"
#include "structures.h"
#include "utils.h"
#include "arena.h"

int execute_not_instruction(
    UNUSED arena_t *arena,
    process_data_t *process,
    UNUSED instruction_t *instruction)
{
    process->pc = update_program_counter(process->pc, 1);
    return 0;
}
