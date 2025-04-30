/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** debugging.c
*/

#include "corewar.h"
#include <stdint.h>

void print_programs_data(
    program_data_t **progs,
    uint8_t robot_count)
{
    program_data_t *prog = NULL;

    for (uint8_t i = 0; i < robot_count; i++) {
        prog = progs[i];
        printf("FILENO: %d\nPROG NUMBER: %d\nPROG ADRESS: %d\n",
            prog->stream->_fileno, prog->prog_number, prog->prog_adress);
    }
}
