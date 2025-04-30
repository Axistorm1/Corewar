/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** check_args.c
*/

#include "corewar.h"
#include "errors.h"
#include <stdio.h>

static int identify_arg(char *arg)
{
    if (!my_strcmp(arg, "-h"))
        return -1;
    if (!my_strcmp(arg, "-dump"))
        return 0;
    if (!my_strcmp(arg, "-n"))
        return 1;
    if (!my_strcmp(arg, "-a"))
        return 2;
    return 3;
}

static bool handle_dump(
    corewar_data_t *data,
    char **argv,
    int *i,
    UNUSED int tmp)
{
    if (!argv[*i + 1] || !my_str_isdigit(argv[*i + 1]))
        return write_error(BAD_VALUE, argv[*i], -1) != NULL;
    *i += 1;
    data->nbr_cycle = my_atol(argv[*i]);
    return true;
}

static program_data_t *init_program(
    char *name,
    int prog_number,
    int prog_adress)
{
    program_data_t *data = my_calloc(1, sizeof(program_data_t));

    data->stream = fopen(name, "r");
    data->prog_number = prog_number;
    data->prog_adress = prog_adress;
    return data;
}

static bool handle_n(
    corewar_data_t *data,
    char **argv,
    int *i,
    int tmp)
{
    int prog_num = -1;

    if (!argv[*i + 2])
        return write_error(MISSING_CHAMPION, NULL, -1) != NULL;
    if (!argv[*i + 1] || !my_str_isdigit(argv[*i + 1]))
        return write_error(BAD_VALUE, argv[*i], -1) != NULL;
    prog_num = my_atoi(argv[*i + 1]);
    *i += 2;
    if (identify_arg(argv[*i]) == 2 && tmp == -1)
        return handle_a(data, argv, i, prog_num);
    data->programs[data->robot_count] = init_program(argv[*i], prog_num, tmp);
    data->robot_count++;
    return true;
}

bool handle_a(
    corewar_data_t *data,
    char **argv,
    int *i,
    int tmp)
{
    int prog_adr = -1;

    if (!argv[*i + 2])
        return write_error(MISSING_CHAMPION, NULL, -1) != NULL;
    if (!argv[*i + 1] || !my_str_isdigit(argv[*i + 1]))
        return write_error(BAD_VALUE, argv[*i], -1) != NULL;
    prog_adr = my_atoi(argv[*i + 1]);
    *i += 2;
    if (identify_arg(argv[*i]) == 1 && tmp == -1)
        return handle_n(data, argv, i, prog_adr);
    data->programs[data->robot_count] = init_program(argv[*i], tmp, prog_adr);
    data->robot_count++;
    return true;
}

// assume all unknown are standalone champion files
static bool handle_unknown(
    corewar_data_t *data,
    char **argv,
    int *i,
    int tmp)
{
    data->programs[data->robot_count] = init_program(argv[*i], tmp, tmp);
    data->robot_count++;
    return true;
}

corewar_data_t *check_args(
    int argc,
    char **argv,
    corewar_data_t *data)
{
    int arg_type = 0;
    bool (*funcs[4])(corewar_data_t *, char **, int *, int) = {
        handle_dump, handle_n, handle_a, handle_unknown};

    for (int i = 1; i < argc; i++) {
        arg_type = identify_arg(argv[i]);
        if (!funcs[arg_type](data, argv, &i, -1))
            return NULL;
    }
    return data;
}
