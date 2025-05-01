/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** structures.h
*/

#ifndef STRUCTURES_H_
    #define STRUCTURES_H_

    #include <stdint.h>
    #include <stdbool.h>
    #include "op.h"

    #define PACKED [[gnu::packed]]

typedef uint8_t byte1_t;
typedef uint16_t byte2_t;
typedef uint32_t byte4_t;
typedef uint64_t byte8_t;
typedef int8_t sbyte1_t;
typedef int16_t sbyte2_t;
typedef int32_t sbyte4_t;
typedef int64_t sbyte8_t;

typedef enum
PACKED op_codes_e {
    LIVE,
    LD,
    ST,
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    ZJMP,
    LDI,
    STI,
    FORK,
    LLD,
    LLDI,
    LFORK,
    AFF
} op_code_t;

typedef enum
PACKED param_type_e {
    PARAM_NOTHING,
    PARAM_DIR,
    PARAM_INDEX,
    PARAM_IND,
    PARAM_REG
} param_type_t;

typedef union
PACKED parameter_u {
    sbyte4_t dir;
    sbyte2_t index;
    byte2_t ind;
    byte1_t reg;
} parameter_t;

typedef struct
PACKED instruction_s {
    op_code_t op_code;
    byte1_t coding_byte;
    param_type_t param_types[3];
    parameter_t params[3];
    byte1_t size;
} instruction_t;

typedef struct
PACKED robot_info_s {
    char *filename;
    header_t *header;
    byte1_t *memory;
    byte4_t process_count;
    byte2_t prog_num;
    byte2_t mem_adr;
    bool alive;
} robot_info_t;

typedef struct
PACKED corewar_data_s {
    robot_info_t **robots;
    byte4_t dump_cycle;
    byte2_t robot_count;
    bool usage;
    bool grapical_env;
} corewar_data_t;

// also update original->alive on live instruction
typedef struct
PACKED process_data_s {
    struct process_data_s *parent;
    robot_info_t *robot;
    sbyte4_t registers[REG_NUMBER];
    byte4_t remaining_cycles;
    byte4_t cycle_born;
    byte2_t program_counter;
    byte2_t child_count;
    instruction_t *current_instruction;
    bool carry;
    bool alive;
} process_data_t;

typedef struct
PACKED arena_s {
    byte4_t ownership_map[MEM_SIZE];
    byte1_t memory[MEM_SIZE];
    process_data_t **processes;
    byte4_t process_count;
    byte4_t total_cycles;
    sbyte2_t current_cycle;
    sbyte2_t cycle_to_die;
    byte2_t robots_alive;
} arena_t;

#endif /* STRUCTURES_H_ */
