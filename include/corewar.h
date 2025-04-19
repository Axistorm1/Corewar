/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** corewar.h
*/

#ifndef COREWAR_H_
    #define COREWAR_H_

    #include <stdbool.h>
    #include "my_string.h"
    #include "my_stype.h"
    #include "my_stdlib.h"

    // Args handling
    #define USAGE_ARG "-h"
    #define DUMP_ARG "-dump"

void display_usage(void);

typedef struct program_data_s {
    char *prog_file;
    char *prog_name;
    int prog_number;
    int prog_adress;
} program_data_t;

typedef struct corewar_data_s {
    program_data_t *programs;
    long nbr_cycle;
    bool usage;
    bool graphical_env;
    char padding[2];
} corewar_data_t;

#endif /* COREWAR_H_ */
