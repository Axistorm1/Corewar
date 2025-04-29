/*
** EPITECH PROJECT, 2025
** header
** File description:
** header
*/
#include "../../include/op.h"
#include "../../include/corewar.h"
#include "../../include/parsing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static unsigned int get_param(
    char *param,
    instruction_t *instruction)
{
    unsigned int value = (unsigned int)(((param[0] - '0') * 10) +
        (param[1] - '0'));

    if (value == 10 && index_check(instruction) == 1)
        value = P_INDEX;
    return value;
}

//Can be used to check if the param value is correct for error handling
static void get_values(
    char *bin,
    int type,
    instruction_t *instruction,
    int i)
{
    if (type == P_INDEX) {
        instruction->params[i].index = (u_int16_t)(bin[0] + bin[1]);
        instruction->param_type[i] = PARAM_INDEX;
    }
    if (type == P_REG) {
        instruction->params[i].reg = (u_int8_t)bin[0];
        instruction->param_type[i] = PARAM_REG;
    }
    if (type == P_DIRECT) {
        instruction->param_type[i] = PARAM_DIR;
        instruction->params[i].dir = bin[0] + bin[1] + bin[2] + bin[3];
    }
    if (type == P_INDIRECT) {
        instruction->params[i].ind = (u_int16_t)(bin[0] + bin[1]);
        instruction->param_type[i] = PARAM_IND;
    }
}

static int store_params(
    instruction_t *instruction,
    unsigned int value_arr[MAX_ARGS],
    char *bin)
{
    int idx = 0;

    for (int i = 0; i != MAX_ARGS || value_arr[i] != NOTHING; i++) {
        get_values(&bin[idx], (int)value_arr[i], instruction, i);
        if (value_arr[i] == P_REG)
            idx++;
        if (value_arr[i] == P_DIRECT)
            idx += 4;
        if (value_arr[i] == P_INDIRECT)
            idx += 2;
        if (value_arr[i] == P_INDEX)
            idx += 2;
    }
    return idx;
}

int parse_params(
    instruction_t *instruction,
    char *bin)
{
    char buffer[9] = {0};
    unsigned int value;
    int i = 0;
    unsigned int value_arr[MAX_ARGS] = {0};
    int bytes_read = special_inst(instruction, bin);

    if (bytes_read != 0)
        return bytes_read;
    int_to_bin(instruction->coding_byte, buffer);
    while (1) {
        value = get_param(&buffer[i], instruction);
        value_arr[i / 2] = value;
        i += 2;
        if (i > 6)
            break;
    }
    bytes_read = store_params(instruction, value_arr, bin);
    return bytes_read;
}
