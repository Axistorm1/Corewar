/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** parse_params.c
*/

#include "op.h"
#include "parsing.h"
#include "structures.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

static unsigned int get_param(
    char *param)
{
    unsigned int value = (unsigned int)(((param[0] - '0') * 10) +
        (param[1] - '0'));

    return value;
}

//Can be used to check if the param value is correct for error handling
static void get_values(
    u_char *bin,
    int type,
    instruction_t *instruction,
    int i)
{
    if (type == P_INDEX) {
        instruction->params[i].index = (int16_t)(bin[0] + bin[1]);
        instruction->param_types[i] = PARAM_INDEX;
    }
    if (type == P_REG) {
        instruction->params[i].reg = (u_int8_t)bin[0];
            instruction->param_types[i] = PARAM_REG;
    }
    if (type == P_DIRECT) {
        instruction->param_types[i] = PARAM_DIR;
        instruction->params[i].dir = bin[0] + bin[1] + bin[2] + bin[3];
    }
    if (type == P_INDIRECT) {
        instruction->params[i].ind = (u_int16_t)(bin[0] + bin[1]);
        instruction->param_types[i] = PARAM_IND;
    }
}

static int store_params(
    instruction_t *instruction,
    unsigned int type_arr[MAX_ARGS],
    u_char *bin)
{
    int idx = 0;

    for (int i = 0; i < MAX_ARGS; i++) {
        get_values(&bin[idx], (int)type_arr[i], instruction, i);
        if (type_arr[i] == P_REG)
            idx += REGIS_SIZE;
        if (type_arr[i] == P_DIRECT)
            idx += DIR_SIZE;
        if (type_arr[i] == P_INDIRECT)
            idx += IND_SIZE;
        if (type_arr[i] == P_INDEX)
            idx += IND_SIZE;
    }
    return idx;
}

int parse_params(
    instruction_t *instruction,
    u_char *bin)
{
    char buffer[CHAR_CODING_B] = {0};
    unsigned int value;
    unsigned int type_arr[MAX_ARGS] = {0};
    int bytes_read = special_inst(instruction, (char *)bin);

    if (bytes_read != 0)
        return bytes_read;
    int_to_bin(instruction->coding_byte, buffer);
    for (uint i = 0; i < 6; i += 2) {
        value = get_param(&buffer[i]);
        type_arr[i / 2] = value;
    }
    index_check(instruction, type_arr);
    bytes_read = store_params(instruction, type_arr, bin);
    return bytes_read;
}
