/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** corewar.h
*/

#ifndef COREWAR_H_
    #define COREWAR_H_

    #include <stdbool.h>
    #include <stdint.h>
    #include "my_string.h"
    #include "my_stype.h"
    #include "my_stdlib.h"
    #include "structures.h"

    // Args handling
    #define USAGE_ARG "-h"
    #define DUMP_ARG "-dump"

    #define PACKED [[gnu::packed]]
    #define UNUSED [[gnu::unused]]

void display_usage(void);

corewar_data_t *check_args(int argc, const char **argv, corewar_data_t *data);
// handle_a isn't static as it wouldn't be able to get called from handle_n
bool handle_a(corewar_data_t *data, const char **argv, int *i, int tmp);

// debugging
void print_programs_data(program_data_t **progs, uint8_t robot_count);

#endif /* COREWAR_H_ */
