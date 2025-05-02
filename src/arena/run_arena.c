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
#include <time.h>
#include <unistd.h>

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
            * (arena->process_count + 2));
        arena->processes[arena->process_count] =
            create_new_process(NULL, robots[i]);
        arena->processes[arena->process_count + 1] = NULL;
        arena->process_count++;
    }
    arena->robots_alive = robot_count;
    return arena;
}

static bool keep_running(arena_t *arena)
{
    arena->current_cycle++;
    arena->total_cycles++;
    if (arena->current_cycle > arena->cycle_to_die) {
        arena->current_cycle = 0;
        kill_non_alive_processes(arena);
        if (arena->nbr_live >= NBR_LIVE) {
            arena->cycle_to_die -= CYCLE_DELTA;
            arena->nbr_live = 0;
        }
    }
    if (arena->cycle_to_die <= 0 || arena->robots_alive <= 1
        || arena->process_count <= 1)
        return false;
    return true;
}

static void run_arena(arena_t *arena)
{
    while (keep_running(arena)) {
        run_processes(arena);
        printf("\033[0J\033[H\n");
        print_arena(arena);
        print_arena_data(arena);
        struct timespec tim, tim2;
        tim.tv_sec = 0;
        tim.tv_nsec = 20000000;
        nanosleep(&tim , &tim2);
    }
}

arena_t *create_arena(corewar_data_t *data)
{
    arena_t *arena = my_calloc(1, sizeof(arena_t));

    arena->cycle_to_die = CYCLE_TO_DIE;
    load_robots_to_arena(data->robots, data->robot_count, arena);
    run_arena(arena);
    free_processes(arena->processes, arena->process_count);
    return arena;
}
