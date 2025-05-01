/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** arena.h
*/


#ifndef ARENA_H_
    #define ARENA_H_

    #include "structures.h"

    #define PROCESS_LIMIT 2e24

arena_t *create_arena(corewar_data_t *data);
void write_to_arena(arena_t *arena, byte2_t adress,
    byte1_t data, byte4_t prog_number);
void print_arena(arena_t *arena);

process_data_t *create_new_process(
    process_data_t *parent, robot_info_t *robot, byte4_t current_cycle);
int run_processes(arena_t *arena);
void *free_processes(process_data_t **processes, byte4_t process_count);

// instructions
int execute_live_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);

#endif /* ARENA_H_ */
