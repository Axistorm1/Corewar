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
    #include <stdio.h>
    #include "my_string.h"
    #include "my_stype.h"
    #include "my_stdlib.h"

    // Args handling
    #define USAGE_ARG "-h"
    #define DUMP_ARG "-dump"

    #define PACKED [[gnu::packed]]
    #define UNUSED [[gnu::unused]]

void display_usage(void);

typedef union parameter_type_u {
    uint8_t reg;
    int dir;
    uint16_t ind;
} parameter_type_t;

typedef struct
PACKED instruction_s {
    parameter_type_t params[3];
    uint8_t op_code;
    uint8_t coding_byte;
    int bytes_pos;
} instruction_t;

typedef struct
PACKED program_data_s {
    FILE *stream;
    int prog_number;
    int prog_adress;
} program_data_t;

typedef struct
PACKED corewar_data_s {
    program_data_t *programs[4];
    long nbr_cycle;
    uint8_t robot_count;
    bool usage;
    bool graphical_env;
} corewar_data_t;

corewar_data_t *check_args(int argc, char **argv, corewar_data_t *data);
// handle_a isn't static as it wouldn't be able to get called from handle_n
bool handle_a(corewar_data_t *data, char **argv, int *i, int tmp);

#endif /* COREWAR_H_ */
