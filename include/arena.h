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

#endif /* ARENA_H_ */
