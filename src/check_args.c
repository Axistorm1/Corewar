#include "corewar.h"
#include "errors.h"
#include "op.h"
#include "structures.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static int identify_arg(const char *arg)
{
    if (!strcmp(arg, "-h"))
        return -1;
    if (!strcmp(arg, "-dump"))
        return 0;
    if (!strcmp(arg, "-n"))
        return 1;
    if (!strcmp(arg, "-a"))
        return 2;
    return 3;
}

static bool handle_dump(corewar_data_t *data, const char **argv, int *i,
                        UNUSED int tmp)
{
    if (!argv[*i + 1] || !my_str_isdigit(argv[*i + 1]))
        return write_error(BAD_VALUE, argv[*i], -1);
    *i += 1;
    data->dump_cycle = (uint32_t)atol(argv[*i]);
    if (data->dump_cycle > MAX_CYCLES)
        write_error(MAX_CYCLE, NULL, data->dump_cycle);
    return true;
}

static FILE *open_file(const char *filename, char *mode)
{
    struct stat sb;
    FILE       *fptr   = NULL;
    int         buffer = 0;

    if (stat(filename, &sb) == -1)
        return write_error(FILE_NOT_FOUND, filename, -1);
    if (sb.st_size < 1)
        return write_error(EMPTY_FILE, filename, -1);
    if (sb.st_size < (long)sizeof(header_t))
        return write_error(INCORRECT_HEADER, filename, -1);
    fptr = fopen(filename, mode);
    fread(&buffer, sizeof(byte4_t), 1, fptr);
    if (strcmp(strrchr(filename, '.'), ".cor") ||
        swap_endian((u_int)(buffer)) != COREWAR_EXEC_MAGIC)
    {
        fclose(fptr);
        return write_error(NOT_COR_FILE, filename, -1);
    }
    fseek(fptr, 0, 0);
    return fptr;
}

robot_info_t *init_robot(const char *filename, int prog_number, int prog_adress)
{
    FILE         *fptr   = open_file(filename, "r");
    robot_info_t *info   = calloc(1, sizeof(robot_info_t));
    header_t     *header = calloc(1, sizeof(header_t));

    if (!fptr)
        return NULL;
    fread(header, sizeof(header_t), 1, fptr);
    header->prog_size = (int)swap_endian((uint)header->prog_size);
    info->memory      = calloc((ulong)header->prog_size, sizeof(byte1_t));
    fread(info->memory, sizeof(byte1_t), (ulong)header->prog_size, fptr);
    fclose(fptr);
    if (!header || !info->memory)
        return write_error(INCORRECT_FILE, filename, -1);
    info->filename = strdup(filename);
    info->header   = header;
    info->prog_num = (byte2_t)prog_number;
    info->mem_adr  = (byte2_t)prog_adress;
    return info;
}

static bool handle_n(corewar_data_t *data, const char **argv, int *i, int tmp)
{
    int prog_num = -1;

    if (!argv[*i + 2])
        return write_error(MISSING_CHAMPION, NULL, -1);
    if (!argv[*i + 1] || !my_str_isdigit(argv[*i + 1]))
        return write_error(BAD_VALUE, argv[*i], -1);
    prog_num = atoi(argv[*i + 1]);
    if (prog_num == 0)
        return write_error(PROG_NUM_0, argv[*i], -1);
    if (prog_num > UINT16_MAX)
        return write_error(PROG_NUM_OUT_OF_BOUNDS, argv[*i], -1);
    *i += 2;
    if (identify_arg(argv[*i]) == 2 && tmp == -1)
        return handle_a(data, argv, i, prog_num);
    data->robots[data->robot_count] = init_robot(argv[*i], prog_num, tmp);
    if (data->robots[data->robot_count])
        data->robot_count++;
    else
        return false;
    return true;
}

bool handle_a(corewar_data_t *data, const char **argv, int *i, int tmp)
{
    int prog_adr = -1;

    if (!argv[*i + 2])
        return write_error(MISSING_CHAMPION, NULL, -1);
    if (!argv[*i + 1] || !my_str_isdigit(argv[*i + 1]))
        return write_error(BAD_VALUE, argv[*i], -1);
    prog_adr = atoi(argv[*i + 1]) % MEM_SIZE;
    *i += 2;
    if (identify_arg(argv[*i]) == 1 && tmp == -1)
        return handle_n(data, argv, i, prog_adr);
    data->robots[data->robot_count] = init_robot(argv[*i], tmp, prog_adr);
    if (data->robots[data->robot_count])
        data->robot_count++;
    else
        return false;
    return true;
}

// assume all unknown values are standalone champion files
static bool handle_unknown(corewar_data_t *data, const char **argv, int *i,
                           int tmp)
{
    data->robots[data->robot_count] = init_robot(argv[*i], tmp, tmp);
    if (data->robots[data->robot_count])
        data->robot_count++;
    else
        return false;
    return true;
}

static bool check_corewar_data(corewar_data_t *data)
{
    robot_info_t *robot      = data->robots[0];
    long          total_size = 0;

    if (data->robot_count == 0 && BONUS_MODE == 0)
        return write_error(NOT_ENOUGH_ROBOTS, NULL, -1);
    if (data->robot_count == 1)
        write_error(ONE_ROBOT, robot->header->prog_name, -1);
    for (byte2_t i = 0; i < data->robot_count; i++)
    {
        robot = data->robots[i];
        total_size += robot->header->prog_size;
        if (robot->header->prog_size > MEM_SIZE)
            return write_error(ROBOT_TOO_BIG, robot->header->prog_name, -1);
    }
    if (total_size > MEM_SIZE)
        write_error(ROBOTS_EAT_OTHERS, NULL, -1);
    return true;
}

corewar_data_t *check_args(int argc, const char **argv, corewar_data_t *data)
{
    int arg_type          = 0;
    bool (*funcs[4])(corewar_data_t *, const char **, int *,
                     int) = {handle_dump, handle_n, handle_a, handle_unknown};

    for (int i = 1; i < argc; i++)
    {
        arg_type = identify_arg(argv[i]);
        if (arg_type == -1)
        {
            data->usage = true;
            return data;
        }
        if (!funcs[arg_type](data, argv, &i, -1))
        {
            free_corewar_data(data);
            return NULL;
        }
    }
    if (!check_corewar_data(data))
    {
        free_corewar_data(data);
        return NULL;
    }
    return data;
}
