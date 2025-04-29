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

    // Args handling
    #define USAGE_ARG "-h"
    #define DUMP_ARG "-dump"
void display_usage(void);

typedef union parameter_type_u {
    uint8_t reg;
    int dir;
    uint16_t ind;
    int16_t index;
} parameter_type_t;


typedef enum {
    PARAM_NOTHING,
    PARAM_REG,
    PARAM_DIR,
    PARAM_IND,
    PARAM_INDEX
} param_type_t;

typedef struct instruction_s {
    parameter_type_t params[3];
    param_type_t param_type[3];
    uint8_t op_code;
    uint8_t coding_byte;
    char padding[2];
    int bytes_pos;
} instruction_t;

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

corewar_data_t *check_args(int argc, char **argv, corewar_data_t *data);
#endif /* COREWAR_H_ */
