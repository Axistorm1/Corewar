#include "parsing.h"
#include "structures.h"
#include "utils.h"
#include <stdlib.h>
#include "corewar.h"
#include <string.h>
#include <unistd.h>
#include "arena.h"
#include "bonus.h"

static int (* const instructions[])
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
    robot_info_t *robot)
{
    process_data_t *process = malloc(sizeof(process_data_t));

    memset(process, 0, sizeof(process_data_t));
    process->parent = parent;
    process->robot = robot;
    process->pc = robot->mem_adr;
    process->registers[0] = robot->prog_num;
    if (parent) {
        memcpy(process->registers, parent->registers,
            REG_SIZE * REG_NUMBER);
        process->pc = parent->pc;
    }
    robot->process_count++;
    return process;
}

// need to handle circular memory accesses
static void handle_new_instruction(
    process_data_t *proc,
    arena_t *arena)
{
    int update_pc = 0;

    if (proc->instruction)
        update_pc = instructions[proc->instruction->op_code]
            (arena, proc, proc->instruction);
    if (update_pc == 1)
        proc->pc = update_program_counter(proc->pc, proc->instruction->size);
    proc->instruction = analyze_memory(&arena->memory[proc->pc]);
    if (!proc->instruction || proc->instruction->op_code > LAST_INSTRUCTION) {
        proc->instruction->op_code = 0;
        proc->instruction->coding_byte = 0;
        proc->instruction->size = 1;
        proc->pc = update_program_counter(proc->pc, 1);
        return;
    }
    proc->wait_cycles = (byte4_t)op_tab[proc->instruction->op_code].nbr_cycles;
}

void handle_non_alive(arena_t *arena, byte4_t i)
{
    char tmp_bonus[BONUS_DEAD_MESSAGE_SIZE];

    arena->processes[i]->robot->process_count--;
    if (arena->processes[i]->robot->process_count == 0)
        arena->processes[i]->robot->alive = false;
    if (BONUS_MODE == 1) {
        memset(tmp_bonus, 0, BONUS_DEAD_MESSAGE_SIZE);
        strcat(tmp_bonus, arena->processes[i]->robot->header->prog_name);
        strcat(tmp_bonus, " died. Rest in piss.");
        update_console_window(tmp_bonus,
            arena->processes[i]->robot->prog_num, arena->total_cycles);
        death_audio();
    }
    free(arena->processes[i]);
    arena->process_count--;
    arena->processes[i] = arena->processes[arena->process_count];
    arena->dead_process_count++;
}

void kill_non_alive_processes(arena_t *arena)
{
    byte4_t i = 0;

    while (i < arena->process_count)
        if (!arena->processes[i]->alive)
            handle_non_alive(arena, i);
        else {
            arena->processes[i]->alive = false;
            i++;
        }
}

void run_processes(arena_t *arena)
{
    process_data_t *ptr = NULL;

    for (byte4_t i = 0; i < arena->process_count; i++) {
        ptr = arena->processes[i];
        if (ptr->wait_cycles == 0 && ptr)
            handle_new_instruction(ptr, arena);
        ptr->wait_cycles--;
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
