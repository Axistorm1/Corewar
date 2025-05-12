/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** run_arena.c
*/

#include "op.h"
#include "structures.h"
#include "corewar.h"
#include "my_stdlib.h"
#include "my_string.h"
#include "arena.h"
#include "bonus.h"
#include "utils.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// this will certainly crash if the prog size of a robot is > 6144
static void initialize_robot_in_memory(
    arena_t *arena,
    robot_info_t *robot)
{
    byte2_t size = MEM_SIZE - robot->mem_adr;

    if (robot->mem_adr + robot->header->prog_size >= MEM_SIZE) {
        my_memcpy(&arena->memory[robot->mem_adr], robot->memory, size);
        my_memcpy(&arena->memory[0], &robot->memory[size],
            (ulong)robot->header->prog_size - size);
        for (byte2_t j = 0; j < size; j++)
            arena->ownership_map[robot->mem_adr + j] = robot->prog_num;
        for (byte2_t j = 0; j < robot->header->prog_size - size; j++)
            arena->ownership_map[0 + j] = robot->prog_num;
    } else {
        my_memcpy(&arena->memory[robot->mem_adr], robot->memory,
        (ulong)robot->header->prog_size);
        for (int j = 0; j < robot->header->prog_size; j++)
            arena->ownership_map[robot->mem_adr + j] = robot->prog_num;
    }
}

static arena_t *load_robots_to_arena(
    robot_info_t **robots,
    byte2_t robot_count,
    arena_t *arena)
{
    arena->processes = malloc(sizeof(process_data_t *) * 1);
    arena->processes[0] = NULL;
    for (byte2_t i = 0; i < robot_count; i++) {
        initialize_robot_in_memory(arena, robots[i]);
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

static bool keep_running(arena_t *arena, corewar_data_t *data)
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
    arena->robots_alive = 0;
    for (byte2_t i = 0; i < data->robot_count; i++)
        if (data->robots[i]->process_count)
            arena->robots_alive++;
    if (arena->cycle_to_die <= 0 || arena->robots_alive <= 1
        || arena->process_count <= 1)
        return false;
    return true;
}

static void dump_memory(arena_t *arena)
{
    for (byte2_t i = 0; i < MEM_SIZE; i += 32) {
        for (byte1_t j = 0; j < 32; j++)
            my_puts_hexa(arena->memory[i + j], 2);
        my_puts("");
    }
}

static void run_arena(arena_t *arena, corewar_data_t *data)
{
    while (keep_running(arena, data)
        && arena->total_cycles < data->dump_cycle) {
        run_processes(arena);
        if (BONUS_MODE == 1)
            run_ncurses(arena, data);
    }
    if (data->dump_cycle != (byte4_t)-1)
        dump_memory(arena);
}

arena_t *create_arena(corewar_data_t *data)
{
    arena_t *arena = my_calloc(1, sizeof(arena_t));

    arena->cycle_to_die = CYCLE_TO_DIE;
    load_robots_to_arena(data->robots, data->robot_count, arena);
    run_arena(arena, data);
    free_processes(arena->processes, arena->process_count);
    return arena;
}
