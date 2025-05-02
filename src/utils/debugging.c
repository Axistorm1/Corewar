/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** debugging.c
*/

#include "utils.h"
#include "structures.h"
#include <stdint.h>
#include <stdio.h>

void print_robots_data(
    robot_info_t **robots,
    byte2_t robot_count)
{
    robot_info_t *ptr = NULL;

    for (uint8_t i = 0; i < robot_count; i++) {
        ptr = robots[i];
        printf("/----------------------------------------\\\n"
            "| NAME: %-32s |\n"
            "| NUMBER: %-30d |\n"
            "| ADRESS: %-30d |\n"
            "| SIZE: %-32d |\n"
            "\\----------------------------------------/\n",
            ptr->header->prog_name, ptr->prog_num, ptr->mem_adr,
            ptr->header->prog_size);
    }
}

static char *type_to_str(param_type_t type)
{
    if (type == PARAM_NOTHING)
        return "Nothing";
    if (type == PARAM_DIR)
        return "Direct";
    if (type == PARAM_INDEX)
        return "Index";
    if (type == PARAM_DIRDEX)
        return "Dirdex";
    if (type == PARAM_IND)
        return "Indirect";
    if (type == PARAM_REG)
        return "Register";
    return "Nothing";
}

void print_instruction_data(instruction_t *instruction)
{
    printf("/-----------------------------\\\n"
        "| OP CODE: %-13d      |\n"
        "| CODING BYTE: %-13d  |\n"
        "| PARAM 1: %-8s ->  %-5d |\n"
        "| PARAM 2: %-8s ->  %-5u |\n"
        "| PARAM 3: %-8s ->  %-5u |\n"
        "\\-----------------------------/\n",
        instruction->op_code, instruction->coding_byte,
        type_to_str(instruction->param_types[0]), instruction->params[0].reg,
        type_to_str(instruction->param_types[1]), instruction->params[1].ind,
        type_to_str(instruction->param_types[2]),
        instruction->params[2].index);
}
