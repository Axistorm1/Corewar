/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** parsing.h
*/

#ifndef STRUCTURES_H_
    #define STRUCTURES_H_

    #include "op.h"
    #include <inttypes.h>
    #include <stdbool.h>
#include <stdint.h>
    #include <stdio.h>
#include <sys/types.h>

    #define PACKED [[gnu::packed]]

typedef struct
PACKED parsing_data_s {
    struct instruction_s **instruction;
    int prog_size;
    header_t *header;
} parsing_data_t;

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

typedef struct
PACKED instruction_s {
    parameter_type_t params[3];
    param_type_t param_type[3];
    uint8_t op_code;
    uint8_t coding_byte;
    int bytes_pos;
} instruction_t;

typedef struct
PACKED program_data_s {
    FILE *stream;
    char *filename;
    int prog_number;
    int prog_adress;
    parsing_data_t *data;
} program_data_t;

typedef struct
PACKED corewar_data_s {
    program_data_t **programs;
    long nbr_cycle;
    uint8_t robot_count;
    bool usage;
    bool graphical_env;
} corewar_data_t;

typedef struct
PACKED process_data_s {
    uint32_t parent_process;
    uint32_t registers[REG_NUMBER];
    uint16_t program_counter;
    uint16_t lifetime;
    uint16_t remaining_cycles;
    bool alive;
    bool carry;
} process_data_t;

typedef struct arena_s {
    u_char arena[MEM_SIZE];
    uint process_count;
    process_data_t **processes;
    int current_cycle;
    int cycle_to_die;
} arena_t;

#endif /* STRUCTURES_H_ */
