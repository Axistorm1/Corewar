/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** corewar.h
*/

#include "my_string.h"
#include "structures.h"
#include "parsing.h"
#include "my_stdlib.h"
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *get_parameter_type(
    instruction_t *instruction,
    int i)
{
    if (instruction->param_types[i] == PARAM_REG)
        return " r";
    if (instruction->param_types[i] == PARAM_DIR || instruction->param_types[i] == PARAM_INDEX)
        return " %";
    if (instruction->param_types[i] == PARAM_IND || instruction->param_types[i] == PARAM_DIRDEX)
        return " ";
    return " Bad param";
}

static char *get_parameters(
    instruction_t *instruction,
    char *line_buffer)
{
    size_t len = 0;

    for (int i = 0; i != MAX_ARGS; i++) {
        if (instruction->param_types[i] == PARAM_NOTHING)
            break;
        strcat(line_buffer, get_parameter_type(instruction, i));
        len = strlen(line_buffer);
        if (instruction->param_types[i] == PARAM_REG)
            sprintf(&line_buffer[len], "%d", instruction->params[i].reg + 1);
        if (instruction->param_types[i] == PARAM_DIR)
            sprintf(&line_buffer[len], "%d", instruction->params[i].dir);
        if (instruction->param_types[i] == PARAM_INDEX || instruction->param_types[i] == PARAM_DIRDEX)
            sprintf(&line_buffer[len], "%d", instruction->params[i].index);
        if (instruction->param_types[i] == PARAM_IND)
            sprintf(&line_buffer[len], "%d", instruction->params[i].ind);
        }
    return line_buffer;
}

static char *get_instruction_name(
    instruction_t *instruction)
{
    char *instruct_name[] = {"live", "ld", "st", "add", "sub",
        "and", "or", "xor", "zjmp",
        "ldi", "sti", "fork", "lld",
        "lldi", "lfork", "aff"};

    return instruct_name[instruction->op_code - 1];
}

char **transcribe_dot_s(instruction_t **instructions)
{
    char *line_buffer = alloca(100 * sizeof(char));
    size_t len = str_array_len((char **)instructions);
    char **lines = calloc(len + 1, sizeof(char *));

    for (size_t i = 0; i < len; i++) {
        memset(line_buffer, 0, 100);
        strcat(line_buffer, get_instruction_name(instructions[i]));
        lines[i] = strdup(get_parameters(instructions[i], line_buffer));
    }
    return lines;
}

void write_dot_s_to_file(
    instruction_t **instructions,
    char *filename)
{
    size_t len = strlen(filename);
    char filename_s[len];
    FILE *fptr = NULL;

    filename_s[len - 2] = 0;
    filename_s[len - 1] = 's';
    fptr = fopen(filename_s, "w+");
    char **lines = transcribe_dot_s(instructions);
    for (byte8_t i = 0; lines[i]; i++)
        fwrite(lines[i], strlen(lines[i]), 1, fptr);
}
