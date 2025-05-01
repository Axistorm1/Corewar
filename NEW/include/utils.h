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

ssize_t my_puts(char *str);
ssize_t my_puts_nb(ssize_t nb);
ssize_t my_puts_multiple(size_t n, ...);
unsigned int swap_endian(unsigned int num);
bool handle_a(corewar_data_t *data, const char **argv, int *i, int tmp);
void display_usage(void);

#endif /* UTILS_H_ */
