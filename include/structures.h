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
    #include <ncurses.h>

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
    NONE,
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
    PARAM_NOTHING = 0,
    PARAM_REG = 1,
    PARAM_DIR = 2,
    PARAM_IND = 4,
    PARAM_INDEX = 8,
    PARAM_DIRDEX = 16,
} param_type_t;

    #define ALL_PARAMS 31

typedef union
PACKED parameter_u {
    sbyte4_t dir;
    sbyte2_t index;
    byte2_t ind;
    byte1_t reg;
} parameter_t;

typedef struct
type_and_param_s {
    param_type_t type;
    parameter_t param;
} type_and_param_t;

typedef struct
instruction_s {
    op_code_t op_code;
    byte1_t coding_byte;
    param_type_t types[3];
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
PACKED gap_placement_info_s {
    robot_info_t **robots_in_gap;
    int gap_start;
    int gap_size;
    int positions_count;
} gap_placement_info_t;

// BONUS ONLY
typedef enum active_window_e {
    CHAMPIONS_INFO,
    PROCESSES_INFO,
    ARENA,
    GAME_INFO,
    CONSOLE,
} active_window_t;

// BONUS ONLY
typedef enum signal_type_e {
    NO_SIGNAL,
    SKIP,
    KILL,
    CARRY,
    REVIVE,
} signal_type_t;

// this shit structure is for the bonus part only
typedef struct windows_jungle_s {
    WINDOW *champions;
    WINDOW *processes;
    WINDOW *arena;
    WINDOW *game_info;
    WINDOW *console;
    sbyte4_t arena_window_size;
    sbyte4_t current_robot_info;
    sbyte4_t shown_process;
    sbyte4_t arena_mem_line;
    sbyte4_t source_line;
    byte4_t current_process;
    byte2_t cycling_speed;
    byte1_t active_window;
    byte1_t signal;
    bool cursors;
    bool process_menu;
    bool fullscreen_arena;
    bool source_code;
} windows_jungle_t;

typedef struct
PACKED corewar_data_s {
    robot_info_t **robots;
    byte4_t dump_cycle;
    byte2_t robot_count;
    bool usage;
} corewar_data_t;

typedef struct
PACKED process_data_s {
    struct process_data_s *parent;
    robot_info_t *robot;
    instruction_t *instruction;
    sbyte4_t registers[REG_NUMBER];
    byte4_t wait_cycles;
    byte4_t cycle_born;
    byte2_t pc;
    bool carry;
    bool alive;
} process_data_t;

typedef struct
PACKED arena_s {
    byte4_t ownership_map[MEM_SIZE];
    byte1_t memory[MEM_SIZE];
    process_data_t **processes;
    byte4_t process_count;
    byte4_t dead_process_count;
    byte4_t total_cycles;
    sbyte2_t current_cycle;
    sbyte2_t cycle_to_die;
    byte2_t robots_alive;
    byte1_t nbr_live;
} arena_t;

#endif /* STRUCTURES_H_ */
