/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** check_args.c
*/

#include "corewar.h"
#include "errors.h"
#include "op.h"
#include "structures.h"
#include "my_string.h"
#include "my_stype.h"
#include "my_stdlib.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

static int identify_arg(const char *arg)
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
    const char **argv,
    int *i,
    UNUSED int tmp)
{
    if (!argv[*i + 1] || !my_str_isdigit(argv[*i + 1]))
        return write_error(BAD_VALUE, argv[*i], -1) != NULL;
    *i += 1;
    data->dump_cycle = (uint32_t)my_atol(argv[*i]);
    if (data->dump_cycle > MAX_CYCLES || data->dump_cycle < 0)
        write_error(MAX_CYCLE, NULL, data->dump_cycle);
    return true;
}

static FILE *open_file(const char *filename, char *mode)
{
    struct stat sb;
    FILE *fptr = NULL;

    if (stat(filename, &sb) == -1)
        return write_error(FILE_NOT_FOUND, filename, -1);
    if (sb.st_size < 1)
        return write_error(EMPTY_FILE, filename, -1);
    fptr = fopen(filename, mode);
    return fptr;
}

static robot_info_t *init_robot(
    const char *filename,
    int prog_number,
    int prog_adress)
{
    FILE *fptr = open_file(filename, "r");
    robot_info_t *info = my_calloc(1, sizeof(robot_info_t));
    header_t *header = my_calloc(1, sizeof(header_t));
    byte1_t *memory = NULL;

    if (!fptr)
        return NULL;
    fread(header, sizeof(header_t), 1, fptr);
    header->prog_size = (int)swap_endian((unsigned int)header->prog_size);
    if (!header || !header->prog_size || swap_endian((u_int)header->magic)
        != COREWAR_EXEC_MAGIC) {
        fclose(fptr);
        return NULL;
    }
    memory = my_calloc((unsigned long)header->prog_size, sizeof(byte1_t));
    fread(memory, sizeof(byte1_t), (unsigned long)header->prog_size, fptr);
    if (!memory) {
        fclose(fptr);
        return NULL;
    }
    info->filename = my_strdup(filename);
    info->header = header;
    info->prog_num = (byte2_t)prog_number;
    info->mem_adr = (byte2_t)prog_adress;
    fclose(fptr);
    return info;
}

static bool handle_n(
    corewar_data_t *data,
    const char **argv,
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
    data->robots[data->robot_count] = init_robot(argv[*i], prog_num, tmp);
    if (data->robots[data->robot_count])
        data->robot_count++;
    return true;
}

bool handle_a(
    corewar_data_t *data,
    const char **argv,
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
    data->robots[data->robot_count] = init_robot(argv[*i], tmp, prog_adr);
    if (data->robots[data->robot_count])
        data->robot_count++;
    return true;
}

// assume all unknown values are standalone champion files
static bool handle_unknown(
    corewar_data_t *data,
    const char **argv,
    int *i,
    int tmp)
{
    data->robots[data->robot_count] = init_robot(argv[*i], tmp, tmp);
    if (data->robots[data->robot_count])
        data->robot_count++;
    return true;
}

static bool check_corewar_data(corewar_data_t *data)
{
    if (data->robot_count == 0)
        return write_error(NOT_ENOUGH_ROBOTS, NULL, -1) != NULL;
    if (data->robot_count == 1)
        write_error(ONE_ROBOT, data->robots[0]->filename, -1);
    return true;
}

corewar_data_t *check_args(
    int argc,
    const char **argv,
    corewar_data_t *data)
{
    int arg_type = 0;
    bool (*funcs[4])(corewar_data_t *, const char **, int *, int) = {
        handle_dump, handle_n, handle_a, handle_unknown};

    for (int i = 1; i < argc; i++) {
        arg_type = identify_arg(argv[i]);
        if (arg_type == -1) {
            data->usage = true;
            return data;
        }
        if (!funcs[arg_type](data, argv, &i, -1))
            return NULL;
    }
    if (!check_corewar_data(data))
        return NULL;
    return data;
}
