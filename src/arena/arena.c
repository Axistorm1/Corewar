/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** arena.c
*/

#include <stdlib.h>
#include "op.h"
#include "corewar.h"
#include "parsing.h"
#include "structures.h"
#include "arena.h"
#include "my_stdlib.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// change printf by non banned
static void print_arena(u_char *arena, process_data_t **processes)
{
    u_char tmp = 0;

    system("clear");
    for (int i = 0; i < MEM_SIZE; i++) {
        write(1, "\033[0m", 5);
        if (processes[0]->program_counter == i)
            write(1, "\033[41m", 5);
        if (processes[1]->program_counter == i)
            write(1, "\033[42m", 5);
        tmp = arena[i];
        printf("%02x", tmp);
        fflush(stdout);
    }
    printf("\n");
}

static void load_program_in_memory(
    FILE *stream,
    int prog_adress,
    u_char *arena)
{
    fseek(stream, PROG_START, SEEK_SET);
    fread(&arena[prog_adress], sizeof(u_char), PROG_SIZE_END, stream);
    fclose(stream);
}

static bool run_processes(
    arena_t *arena)
{
    bool any_alive = false;

    for (uint i = 0; i < arena->process_count; i++) {
        if (arena->processes[i]->remaining_cycles == 0)
            arena->processes[i]->alive = true;
            //identify_instruction(&arena[processes[i]->program_counter])
        if (arena->processes[i]->alive)
            any_alive = true;
    }
    return any_alive;
}

static uint run_arena(
    arena_t *arena)
{
    while (run_processes(arena)) {
        arena->current_cycle++;
        if (arena->current_cycle > arena->cycle_to_die) {
            arena->cycle_to_die -= CYCLE_DELTA;
            arena->current_cycle = 0;
        if (arena->cycle_to_die <= 0 || arena->process_count == 0)
            break;
        }
    }
    // return winning process
}

uint load_arena(corewar_data_t *data)
{
    arena_t *arena = malloc(sizeof(arena_t));
    program_data_t *ptr = NULL;
    uint winning_process = 0;

    my_memset(arena, 0, sizeof(arena_t));
    arena->process_count = data->robot_count;
    arena->cycle_to_die = CYCLE_TO_DIE;
    for (uint8_t i = 0; i < data->robot_count; i++) {
        ptr = data->programs[i];
        load_program_in_memory(ptr->stream, ptr->prog_adress, arena->arena);
        arena->processes = realloc(arena->processes, (i + 1) * sizeof(process_data_t *));
        arena->processes[i] = malloc(sizeof(process_data_t));
        my_memset(arena->processes[i], 0, sizeof(process_data_t));
        arena->processes[i]->program_counter = (uint16_t)ptr->prog_adress;
    }
    winning_process = run_arena(arena);
    for (uint i = 0; i < arena->process_count; i++)
        free(arena->processes[i]);
    free(arena->processes);
    free(arena);
    return winning_process;
}
