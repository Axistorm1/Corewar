/*
** EPITECH PROJECT, 2025
** header
** File description:
** header
*/
#include "corewar.h"
#include "op.h"
#include "parsing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


static void save_proc_size(
    parsing_data_t *parse_data,
    char *program)
{
    int i = PROG_SIZE;

    for (; i != PROG_SIZE_END; i++)
        parse_data->prog_size += program[i];
}

static int verify_edge_case(
    instruction_t *instruction)
{
    int edging[] = {1, 12};

    for (int i = 0; i != 2; i++) {
        if (instruction->op_code == edging[i]) {
            instruction->coding_byte = 0;
            return 1;
        }
    }
    return 2;
}

static int analyse_instructions(
    parsing_data_t *parse_data,
    char *buffer)
{
    int i = PROG_START;
    int inst_idx = 0;

    while (1) {
        parse_data->instruction[inst_idx] = my_malloc(sizeof(instruction_t));
        parse_data->instruction[inst_idx]->op_code = (u_int8_t)buffer[i];
        parse_data->instruction[inst_idx]->coding_byte =
            (u_int8_t)buffer[i + 1];
        i += verify_edge_case(parse_data->instruction[inst_idx]);
        i += parse_params(parse_data->instruction[inst_idx], &buffer[i]);
        if (i - PROG_START >= parse_data->prog_size)
            return 1;
        inst_idx++;
    }
    return 1;
}

int parse_champions(
    parsing_data_t *parse_data,
    program_data_t *program_data)
{
    FILE *fptr = fopen(program_data->filename, "r");
    char *buffer = NULL;
    size_t size = 0;
    header_t *header = my_calloc(1, sizeof(header_t));

    fread(header, sizeof(header_t), 1, fptr);
    header->prog_size = swap_endian(header->prog_size);
    parse_data->header = header;
    return 0;
    getline(&buffer, &size, fptr);
    save_proc_size(parse_data, buffer);
    parse_data->instruction = my_calloc(sizeof(instruction_t *),
        (unsigned int)parse_data->prog_size / 3);
    printf("DEBUG : Proc size %d\n", parse_data->prog_size);
    if (analyse_instructions(parse_data, buffer) == -1) {
        free(buffer);
        fclose(fptr);
        return -1;
    }
    fclose(fptr);
    debug_info(parse_data);
    free(buffer);
    return 0;
}
