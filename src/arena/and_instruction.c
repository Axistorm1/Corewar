/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** and_instruction.c
*/

#include "structures.h"
#include "arena.h"

int execute_and_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction)
{
    sbyte8_t first_value = 0;
    sbyte8_t second_value = 0;

    first_value =
        get_data_in_param(&(type_and_param_t){instruction->param_types[0],
            instruction->params[0]}, ALL_PARAMS, arena, process);
}
