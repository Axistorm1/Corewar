/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** handle_processes.c
*/

#include "op.h"
#include "parsing.h"
#include "structures.h"
#include "my_string.h"
#include <stdlib.h>
#include <arena.h>

static int (* const instruction_array[])
    (arena_t *, process_data_t *, instruction_t *) = {
    execute_not_instruction, execute_live_instruction,
    execute_ld_instruction, execute_st_instruction,
    execute_add_instruction, execute_sub_instruction,
    execute_and_instruction, execute_or_instruction,
    execute_xor_instruction, execute_zjmp_instruction,
    execute_ldi_instruction, execute_sti_instruction,
    execute_fork_instruction, execute_lld_instruction,
    execute_lldi_instruction, execute_lfork_instruction,
    execute_aff_instruction};

process_data_t *create_new_process(
    process_data_t *parent,
    robot_info_t *robot,
    byte4_t current_cycle)
{
    process_data_t *process = malloc(sizeof(process_data_t));

    my_memset(process, 0, sizeof(process_data_t));
    process->parent = parent;
    process->robot = robot;
    process->cycle_born = current_cycle;
    process->program_counter = robot->mem_adr;
    robot->process_count++;
    return process;
}

static void handle_new_instruction(
    process_data_t *process,
    arena_t *arena)
{
    int update_pc = 0;

    if (process->current_instruction)
        update_pc = instruction_array[process->current_instruction->op_code]
            (arena, process, process->current_instruction);
    if (update_pc == 1)
        process->program_counter += process->current_instruction->size;
    process->current_instruction =
        analyze_memory(&arena->memory[process->program_counter]);
    process->remaining_cycles =
        (byte4_t)op_tab[process->current_instruction->op_code - 1].nbr_cycles;
}

int run_processes(arena_t *arena)
{
    process_data_t *ptr = NULL;

    for (byte4_t i = 0; i < arena->process_count; i++) {
        ptr = arena->processes[i];
        if (ptr->remaining_cycles == 0)
            handle_new_instruction(ptr, arena);
        ptr->remaining_cycles--;
    }
}

void *free_processes(
    process_data_t **processes,
    byte4_t process_count)
{
    for (byte4_t i = 0; i < process_count; i++)
        free(processes[i]);
    free(processes);
    return NULL;
}
