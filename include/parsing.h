/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** parsing.h
*/


#ifndef PARSING_H_
    #define PARSING_H_

    #include "structures.h"
    #include <sys/types.h>

    #define MAX_ARGS 3
    #define CODING_NBR 4
    #define CHAR_CODING_B 9
    // the fuck is msb
    #define MSB 0x8000

    #define P_REG 1
    #define P_INDEX 2
    #define P_DIRDEX 3
    #define P_DIRECT 10
    #define P_INDIRECT 11

    #define REGIS_SIZE 1

    #define INDEX_NBR 4

    #define NOTHING 0

void int_to_bin(int n, char output[9]);

int verify_coding_byte(instruction_t *instruction);

void index_check(
    instruction_t *instruction, unsigned int value_arr[MAX_ARGS]);
int special_inst(instruction_t *instruction, char *bin);
int parse_params(instruction_t *instruction, u_char *bin);

instruction_t *analyze_memory(byte1_t *buffer);

#endif /* PARSING_H_ */
