/*
** EPITECH PROJECT, 2025
** header
** File description:
** header
*/

#include "../../../include/parsing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void debug_info(
    parsing_data_t *parse_data)
{
    printf("DEBUG {\n");
    for (int i = 0; parse_data->instruction[i] != NULL; i++) {
        printf("INDEX %d || ", i);
        printf("OP_CODE %d || coding_byte %d\n", parse_data->instruction[i]->op_code, parse_data->instruction[i]->coding_byte);
        for (int j = 0; j != 3; j++) {
            switch (parse_data->instruction[i]->param_type[j]) {
                case PARAM_NOTHING:
                    printf("params[%d] has no parameter\n", j);
                    break;
                case PARAM_REG:
                    printf("params[%d] is reg: %u\n", j, parse_data->instruction[i]->params[j].reg);
                    break;
                case PARAM_DIR:
                    printf("params[%d] is dir: %d\n", j, parse_data->instruction[i]->params[j].dir);
                    break;
                case PARAM_IND:
                    printf("params[%d] is ind: %u\n", j, parse_data->instruction[i]->params[j].ind);
                    break;
                case PARAM_INDEX:
                    printf("params[%d] is index: %d\n", j, parse_data->instruction[i]->params[j].index);
                    break;
            }
        }
        printf("---------------------------------------------------------\n");
    }
    printf("} DEBUG END\n");
}
