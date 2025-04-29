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
    char *param)
{
    unsigned int value = (unsigned int)(((param[0] - '0') * 10) +
        (param[1] - '0'));

    return value;
}

//Can be used to check if the param value is correct for error handling
static void get_values(
    char *bin,
    int type,
    instruction_t *instruction,
    int i)
{
    if (type == P_REG)
        instruction->params[i].reg = (u_int8_t)bin[0];
    if (type == P_DIRECT)
        instruction->params[i].dir = bin[0] + bin[1];
    if (type == P_INDIRECT)
        instruction->params[i].ind = (u_int16_t)(bin[0] + bin[1] +
            bin[2] + bin[3]);
}

static int store_params(
    instruction_t *instruction,
    unsigned int value_arr[3],
    char *bin)
{
    int idx = 0;

    for (int i = 0; i != 3 || value_arr[i] != NOTHING; i++) {
        if (value_arr[i] == P_REG) {
            get_values(&bin[idx], P_REG, instruction, i);
            instruction->param_type[i] = PARAM_REG;
            idx++;
        }
        if (value_arr[i] == P_DIRECT) {
            get_values(&bin[idx], P_DIRECT, instruction, i);
            idx += 2;
            instruction->param_type[i] = PARAM_DIR;
        }
        if (value_arr[i] == P_INDIRECT) {
            get_values(&bin[idx], P_INDIRECT, instruction, i);
            instruction->param_type[i] = PARAM_IND;
            idx += 4;
        }
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
    unsigned int value_arr[3] = {0};
    int bytes_read = special_inst(instruction, bin);

    if (bytes_read != 0)
        return bytes_read;
    int_to_bin(instruction->coding_byte, buffer);
    while (1) {
        value = get_param(&buffer[i]);
        value_arr[i / 2] = value;
        i += 2;
        if (i > 6)
            break;
    }
    bytes_read = store_params(instruction, value_arr, bin);
    return bytes_read;
}
