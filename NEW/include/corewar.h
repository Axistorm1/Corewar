/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** corewar.h
*/


#ifndef COREWAR_H_
    #define COREWAR_H_

    #include "structures.h"

    #define UNUSED [[gnu::unused]]

    #define MAX_ROBOTS 1023
    #define MAX_CYCLES 236698

corewar_data_t *check_args(int argc, const char **argv, corewar_data_t *data);

#endif /* COREWAR_H_ */
