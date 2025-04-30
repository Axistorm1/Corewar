/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** arena.c
*/

#include "op.h"
#include "corewar.h"
#include "parsing.h"
#include "structures.h"
#include "my_stdlib.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// change printf by non banned
static void print_arena(u_char *arena)
{
    u_char tmp = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        tmp = arena[i];
        printf("%02x", tmp);
    }
}

static void load_program_in_memory(
    program_data_t *data,
    u_char *arena)
{
    unsigned long prog_size = (ulong)data->data->header->prog_size;

    printf("PROG NAME: %s\n", data->data->header->prog_name);
    printf("PROG SIZE: %ld\n", prog_size);
    fseek(data->stream, PROG_START, SEEK_SET);
    fread(&arena[data->prog_adress], sizeof(u_char), PROG_SIZE_END, data->stream);
}

int run_arena(corewar_data_t *data)
{
    u_char *arena = my_calloc(sizeof(u_char), MEM_SIZE);

    for (uint8_t i = 0; i < data->robot_count; i++)
        load_program_in_memory(data->programs[i], arena);
    print_arena(arena);
    return 0;
}
