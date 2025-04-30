/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** arena.h
*/

#ifndef ARENA_H_
    #define ARENA_H_

    #include "corewar.h"
    #include <sys/types.h>

    #define PACKED [[gnu::packed]]
    #define UNUSED [[gnu::unused]]

uint load_arena(corewar_data_t *data);

#endif /* ARENA_H_ */
