/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** parse_special_params.c
*/

#include "parsing.h"
#include "structures.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

void index_check(
    instruction_t *instruction,
    unsigned int value_arr[MAX_ARGS])
{
    int list_index[] = {LDI, STI, LLDI, LFORK};
    int is_index = 0;

    for (int i = 0; i != INDEX_NBR; i++)
        if (instruction->op_code == list_index[i])
            is_index = 1;
    if (is_index == 0)
        return;
    for (int j = 0; j != MAX_ARGS; j++) {
        if (value_arr[j] == P_INDIRECT)
            value_arr[j] = P_INDEX;
        if (value_arr[j] == P_DIRECT)
            value_arr[j] = P_DIRDEX;
    }
}

static void compute_index(
    sbyte2_t value,
    instruction_t *instruction)
{
    if (value & MSB)
        instruction->params[0].index = (int16_t)(-((~value + 1) & MSB_CONST));
    else
        instruction->params[0].index = (int16_t)value;
}

int special_inst(
    instruction_t *instruction,
    u_char *bin)
{
    if (instruction->op_code == FORK || instruction->op_code == LFORK
        || instruction->op_code == ZJMP) {
        compute_index((sbyte2_t)(bin[0] << BYTE) + bin[1], instruction);
        instruction->types[0] = PARAM_INDEX;
        return 2;
    }
    if (instruction->op_code == 1) {
        instruction->params[0].dir = (bin[0] << BYTE * 3) +
            (bin[1] << BYTE * 2) + (bin[2] << BYTE) + bin[3];
        instruction->types[0] = PARAM_DIR;
        return 4;
    }
    return 0;
}
