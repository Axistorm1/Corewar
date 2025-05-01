/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** run_arena.c
*/

#include "op.h"
#include "parsing.h"
#include "structures.h"
#include "my_stdlib.h"
#include "my_string.h"
#include "arena.h"
#include "utils.h"
#include <stdlib.h>
#include <sys/types.h>

// not too sure of saying that the original is itself when it's the first
process_data_t *create_new_process(
    process_data_t *parent,
    robot_info_t *robot)
{
    process_data_t *process = my_calloc(1, sizeof(process_data_t));

    process->parent = parent;
    process->robot = robot;
    return process;
}

// handle robots that wrap around memory
static arena_t *load_robots_to_arena(
    robot_info_t **robots,
    byte2_t robot_count,
    arena_t *arena)
{
    arena->processes = malloc(sizeof(process_data_t *) * 1);
    arena->processes[0] = NULL;
    for (byte2_t i = 0; i < robot_count; i++) {
        my_memcpy(&arena->memory[robots[i]->mem_adr], robots[i]->memory,
            (ulong)robots[i]->header->prog_size);
        for (int j = 0; j < robots[i]->header->prog_size; j++)
            arena->ownership_map[robots[i]->mem_adr + j] = robots[i]->prog_num;
        arena->processes = realloc(arena->processes, sizeof(process_data_t *)
            * arena->process_count + 2);
        arena->processes[arena->process_count] =
            create_new_process(NULL, robots[i]);
        arena->processes[arena->process_count + 1] = NULL;
    }
    return arena;
}

static bool keep_running(arena_t *arena)
{
    arena->current_cycle++;
    if (arena->current_cycle > arena->cycle_to_die) {
        arena->cycle_to_die -= CYCLE_DELTA;
        arena->current_cycle = 0;
    if (arena->cycle_to_die <= 0 || arena->robots_alive == 0)
        return false;
    }
    return true;
}

static void run_processes(arena_t *arena)
{
    for (byte4_t i = 0; i < arena->process_count; i++);
}

static void run_arena(arena_t *arena)
{
    instruction_t *tmp = analyze_memory(arena->memory);

    print_instruction_data(tmp);
    while (keep_running(arena)) {
        run_processes(arena);
        //print_arena(arena);
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
