/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** arena_utils.c
*/

#include "arena.h"
#include "utils.h"
#include <unistd.h>

void write_to_arena(
    arena_t *arena,
    byte2_t adress,
    byte1_t data,
    byte4_t prog_number)
{
    arena->memory[adress] = data;
    arena->ownership_map[adress] = prog_number;
}

void print_arena(arena_t *arena)
{
    byte1_t tmp = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        if (i == arena->processes[0]->program_counter)
            write(STDOUT_FILENO, "\033[41m", 5);
        else
            write(STDOUT_FILENO, "\033[0m", 4);
        tmp = arena->memory[i];
        write(STDOUT_FILENO, "\033[38;5;", 7);
        my_puts_nb(arena->ownership_map[i] % 256);
        write(STDOUT_FILENO, "m", 1);
        my_puts_hexa(tmp, 2);
        write(STDOUT_FILENO, " ", 0);
    }
    write(STDOUT_FILENO, "\n", 1);
}
