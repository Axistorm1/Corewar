/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** utils.h
*/


#ifndef UTILS_H_
    #define UTILS_H_

    #include "structures.h"
    #include <stdio.h>

void display_usage(void);

ssize_t my_puts(char *str);
ssize_t my_puts_nb(ssize_t nb);
ssize_t my_puts_hexa(ssize_t nb, size_t leading_zeros);
ssize_t my_puts_multiple(size_t n, ...);

void print_robots_data(robot_info_t **robots, byte2_t robot_count);
void print_instruction_data(instruction_t *instruction);

unsigned int swap_endian(unsigned int num);

bool handle_a(corewar_data_t *data, const char **argv, int *i, int tmp);

#endif /* UTILS_H_ */
