#ifndef ARENA_H_
    #define ARENA_H_

    #include "structures.h"

    #define EMPTY_STR ""

    #define PROCESS_LIMIT 1e6
    #define COLORS_COUNT 256

    #define ASCII_SIZE 256

    #define LAST_INSTRUCTION 16

    #define ERROR_VALUE 1l << 32

    #define BUFFER_SIZE 20
    #define DUMP_LINE_SIZE 32
    #define BONUS_DEAD_MESSAGE_SIZE 150
    #define PLAYER_LINE_SIZE 200

void create_arena(corewar_data_t *data);

void write4_to_arena(arena_t *arena, byte2_t adress, byte4_t data, byte4_t prog_number);

// processes
process_data_t *create_new_process(process_data_t *parent, robot_info_t *robot);
void run_processes(arena_t *arena);
void handle_non_alive(arena_t *arena, byte4_t i);
void kill_non_alive_processes(arena_t *arena);
void *free_processes(process_data_t **processes, byte4_t process_count);

// helper function to get a param from an instruction
sbyte8_t get_data_in_param(
    type_and_param_t *type_and_param,
    byte1_t params_value,
    arena_t *arena,
    process_data_t *process);

// instructions
int execute_add_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_aff_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_and_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_fork_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_ld_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_ldi_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_live_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_lfork_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_lld_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_lldi_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_or_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_st_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_sti_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_sub_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_xor_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_zjmp_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);
int execute_not_instruction(
    arena_t *arena,
    process_data_t *process,
    instruction_t *instruction);

#endif /* ARENA_H_ */
