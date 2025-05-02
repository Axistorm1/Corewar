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
#include <stdio.h>
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

static byte1_t background_color(arena_t *arena, byte2_t pc)
{
    for (byte4_t i = 0; i < arena->process_count; i++) {
        if (pc == arena->processes[i]->pc)
            return arena->processes[i]->robot->prog_num % 255;
    }
    return 255;
}

void print_arena(arena_t *arena)
{
    byte1_t tmp = 0;

    for (byte2_t i = 0; i < MEM_SIZE; i++) {
        tmp = background_color(arena, i);
        if (tmp < 255)
            printf("\033[48;5;%dm", tmp);
        else
            printf("\033[0m");
        tmp = arena->memory[i];
        printf("\033[38;5;%dm%02x",
            arena->ownership_map[i] % COLORS_COUNT, tmp);
    }
    printf("\033[0m\n");
}

void print_arena_data(arena_t *arena)
{
    printf("Cycle: %d/%d Live: %d/%d Process count: %d        \n",
        arena->current_cycle, arena->cycle_to_die, arena->nbr_live,
        NBR_LIVE, arena->process_count);
}

byte2_t update_program_counter(
    byte2_t program_counter,
    sbyte2_t n)
{
    int new = program_counter + n;
    int circular_index = (new % MEM_SIZE + MEM_SIZE) % MEM_SIZE;

    return (byte2_t)circular_index;
}
