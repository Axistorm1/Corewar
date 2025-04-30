/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** corewar.h
*/

#ifndef PARSING_H_
    #define PARSING_H_
    #include "./corewar.h"
    #include <sys/types.h>
    //index tags
    #define PROG_SIZE 136
    #define PROG_SIZE_END 140
    #define PROG_START 2192
    #define P_DIRECT 10
    #define P_REG 1
    #define P_INDEX 2
    #define P_INDIRECT 11
    #define NOTHING 0
    #define INDEX_NBR 1
    #define MSB 0x8000
    #define MAX_ARGS 3
    #define IGNORE __attribute__((unused))
typedef struct {
    int prog_size;
    struct instruction_s **instruction;
} parsing_data_t;

int index_check(instruction_t *instruction);
int special_inst(instruction_t *instruction, char *bin);
void debug_info(parsing_data_t *parse_data);
void int_to_bin(int n, char output[9]);
int parse_params(instruction_t *parse_params, char *bin);
int parse_champions(parsing_data_t *parse_data);
#endif /* PARSING_H_ */
