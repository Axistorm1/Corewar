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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int special_inst(
    instruction_t *instruction,
    char *bin)
{
    if (instruction->op_code == 12) {
        instruction->params[0].index = (uint16_t)(bin[0] + bin[1]);
        instruction->param_type[0] = PARAM_INDEX;
        return 2;
    }
    return 0;
}
