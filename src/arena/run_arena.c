/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** run_arena.c
*/

#include "op.h"
#include "structures.h"
#include "my_stdlib.h"
#include "my_string.h"
#include "arena.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

// make a set of predefined colors (from 0 to 1023)
static void print_arena(arena_t *arena)
{
    byte1_t tmp = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        tmp = arena->memory[i];
        printf("\033[3%um", arena->ownership_map[i]);
        printf("%02x\033[0m", tmp);
        fflush(stdout);
    }
}

static void write_to_arena(
    arena_t *arena,
    byte2_t adress,
    byte1_t data,
    byte4_t prog_number)
{
    arena->memory[adress] = data;
    arena->ownership_map[adress] = prog_number;
}

// handle robots that wrap around memory
static arena_t *load_robots_to_arena(
    robot_info_t **robots,
    byte2_t robot_count,
    arena_t *arena)
{
    for (byte2_t i = 0; i < robot_count; i++) {
        my_memcpy(&arena->memory[robots[i]->mem_adr], robots[i]->memory,
            (ulong)robots[i]->header->prog_size);
        for (int j = 0; j < robots[i]->header->prog_size; j++)
            arena->ownership_map[robots[i]->mem_adr + j] = robots[i]->prog_num;
    }
    return arena;
}

static void run_arena(arena_t *arena)
{
    while (1) {
        arena->current_cycle++;
        if (arena->current_cycle > arena->cycle_to_die) {
            arena->cycle_to_die -= CYCLE_DELTA;
            arena->current_cycle = 0;
        if (arena->cycle_to_die <= 0 || arena->robots_alive == 0)
            break;
        }
    }
}

arena_t *create_arena(corewar_data_t *data)
{
    arena_t *arena = my_calloc(1, sizeof(arena_t));

    arena->cycle_to_die = CYCLE_TO_DIE;
    arena->robots_alive = 1; // remove this once executions start running
    load_robots_to_arena(data->robots, data->robot_count, arena);
    run_arena(arena);
    return arena;
}

// use standard malloc and free for processes
// could create a memory bottleneck if not
