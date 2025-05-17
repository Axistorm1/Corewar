#include "op.h"
#include "parsing.h"
#include "structures.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

static byte4_t get_param(
    char *param)
{
    return (byte4_t)(((param[0] - '0') * 10) + (param[1] - '0'));
}

//Can be used to check if the param value is correct for error handling
static void get_values(
    u_char *bin,
    int type,
    instruction_t *instruction,
    int i)
{
    if (type == P_INDEX || type == P_DIRDEX) {
        instruction->params[i].index = (int16_t)((bin[0] << BYTE) + bin[1]);
        instruction->types[i] = PARAM_INDEX;
        if (type == P_DIRDEX)
            instruction->types[i] = PARAM_DIRDEX;
    }
    if (type == P_REG && bin[0] <= REG_NUMBER) {
        instruction->params[i].reg = (u_int8_t)bin[0] - 1;
        instruction->types[i] = PARAM_REG;
    }
    if (type == P_DIRECT) {
        instruction->types[i] = PARAM_DIR;
        instruction->params[i].dir = (bin[0] << BYTE * 3) +
            (bin[1] << BYTE * 2) + (bin[2] << BYTE) + bin[3];
    }
    if (type == P_INDIRECT) {
        instruction->params[i].ind = (u_int16_t)((bin[0] << BYTE) + bin[1]);
        instruction->types[i] = PARAM_IND;
    }
}

static int store_params(
    instruction_t *instruction,
    unsigned int type_arr[MAX_ARGS],
    u_char *bin)
{
    int idx = 0;

    for (int i = 0; i < MAX_ARGS; i++) {
        get_values(&bin[idx], (int)type_arr[i], instruction, i);
        if (type_arr[i] == P_REG)
            idx += REGIS_SIZE;
        if (type_arr[i] == P_DIRECT)
            idx += DIR_SIZE;
        if (type_arr[i] == P_INDIRECT)
            idx += IND_SIZE;
        if (type_arr[i] == P_INDEX || type_arr[i] == P_DIRDEX)
            idx += IND_SIZE;
    }
    return idx;
}

int parse_params(
    instruction_t *instruction,
    u_char *bin)
{
    char buffer[CHAR_CODING_B] = {0};
    unsigned int value;
    unsigned int type_arr[MAX_ARGS] = {0};
    int bytes_read = special_inst(instruction, bin);

    if (bytes_read != 0)
        return bytes_read;
    int_to_bin(instruction->coding_byte, buffer);
    for (uint i = 0; i < 3; i += 1) {
        value = get_param(&buffer[i * 2]);
        type_arr[i] = value;
    }
    index_check(instruction, type_arr);
    bytes_read = store_params(instruction, type_arr, bin);
    return bytes_read;
}
