/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** arena_utils.c
*/

#include "arena.h"
#include "op.h"
#include "structures.h"
#include "utils.h"
#include "my_string.h"
#include "my_stdlib.h"
#include <unistd.h>

void write1_to_arena(
    arena_t *arena,
    byte2_t adress,
    byte1_t data,
    byte4_t prog_number)
{
    arena->memory[adress] = data;
    arena->ownership_map[adress] = prog_number;
}

void write4_to_arena(
    arena_t *arena,
    byte2_t adress,
    byte4_t data,
    byte4_t prog_number)
{
    arena->memory[adress] = (data >> 24) & 0xFF;
    arena->memory[adress + 1] = (data >> 16) & 0xFF;
    arena->memory[adress + 2] = (data >> 8) & 0xFF;
    arena->memory[adress + 3] = data & 0xFF;
    arena->ownership_map[adress] = prog_number;
    arena->ownership_map[adress + 1] = prog_number;
    arena->ownership_map[adress + 2] = prog_number;
    arena->ownership_map[adress + 3] = prog_number;
}

byte2_t update_program_counter(
    byte2_t program_counter,
    sbyte2_t n)
{
    int new = program_counter + n;
    int circular_index = (new % MEM_SIZE + MEM_SIZE) % MEM_SIZE;

    return (byte2_t)circular_index;
}
