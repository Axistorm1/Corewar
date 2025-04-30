/*
** EPITECH PROJECT, 2025
** header
** File description:
** header
*/
#include "../../include/corewar.h"
#include "../../include/parsing.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
int index_check(
    instruction_t *instruction)
{
    int list_index[] = {11};

    for (int i = 0; i != INDEX_NBR; i++) {
        if (instruction->op_code == list_index[i]) {
            return 1;
        }
    }
    return 0;
}

static void compute_index(
    int value,
    instruction_t *instruction)
{
    if (value & MSB) {
        instruction->params[0].index = -((~value + 1) & 0xFFFF);
    } else {
        instruction->params[0].index = (int16_t)value;
    }
}

int special_inst(
    instruction_t *instruction,
    char *bin)
{
    index_check(instruction);
    if (instruction->op_code == 12) {
        compute_index(bin[0] + bin[1], instruction);
        instruction->param_type[0] = PARAM_INDEX;
        return 2;
    }
    if (instruction->op_code == 1) {
        instruction->params[0].dir = bin[0] + bin[1] + bin[2] + bin[3];
        instruction->param_type[0] = PARAM_DIR;
        return 4;
    }
    if (instruction->op_code == 9) {
        compute_index(bin[0] + bin[1], instruction);
        instruction->param_type[0] = PARAM_INDEX;
        return 2;
    }
    return 0;
}
