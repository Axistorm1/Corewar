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

int special_inst(
    instruction_t *instruction,
    char *bin)
{
    index_check(instruction);
    if (instruction->op_code == 12) {
        instruction->params[0].index = (uint16_t)(bin[0] + bin[1]);
        instruction->param_type[0] = PARAM_INDEX;
        return 2;
    }
    return 0;
}
