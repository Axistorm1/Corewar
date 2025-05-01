/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** parse_special_params.c
*/

#include "parsing.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

static void edge_case_index(
    instruction_t *instruction,
    unsigned int value_arr[MAX_ARGS],
    int j)
{
    if (instruction->op_code == 11 && value_arr[j] == P_DIRECT)
        value_arr[j] = P_INDEX;
    if ((instruction->op_code == 10 || instruction->op_code == 14) &&
        (value_arr[j] == P_INDIRECT || value_arr[j] == P_DIRECT)) {
        value_arr[j] = P_INDEX;
    }
}

void index_check(
    instruction_t *instruction,
    unsigned int value_arr[MAX_ARGS])
{
    int list_index[] = {10, 11, 15, 14};
    int is_index = 0;

    for (int i = 0; i != INDEX_NBR; i++) {
        if (instruction->op_code == list_index[i]) {
            is_index = 1;
        }
    }
    if (is_index == 0)
        return;
    for (int j = 0; j != MAX_ARGS; j++) {
        if (value_arr[j] == P_INDIRECT)
            value_arr[j] = P_INDEX;
        edge_case_index(instruction, value_arr, j);
    }
}

static void compute_index(
    int value,
    instruction_t *instruction)
{
    if (value & MSB)
        instruction->params[0].index = (int16_t)(-((~value + 1) & 0xFFFF));
    else
        instruction->params[0].index = (int16_t)value;
}

int special_inst(
    instruction_t *instruction,
    char *bin)
{
    if (instruction->op_code == 12) {
        compute_index(bin[0] + bin[1], instruction);
        instruction->param_types[0] = PARAM_INDEX;
        return 2;
    }
    if (instruction->op_code == 1) {
        instruction->params[0].dir = bin[0] + bin[1] + bin[2] + bin[3];
        instruction->param_types[0] = PARAM_DIR;
        return 4;
    }
    if (instruction->op_code == 9 || instruction->op_code == 15) {
        compute_index(bin[0] + bin[1], instruction);
        instruction->param_types[0] = PARAM_INDEX;
        return 2;
    }
    return 0;
}
