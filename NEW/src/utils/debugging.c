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
            ptr->header->prog_name, ptr->prog_num, ptr->mem_adr, ptr->header->prog_size);
    }
}
