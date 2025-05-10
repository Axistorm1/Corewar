/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** instructions.c
** The two functions found in this file are really important;
** Any modification to them must be explained;
*/

#include "op.h"
#include "arena.h"
#include "structures.h"

sbyte8_t get_data_in_param_idx_mod(
    type_and_param_t *type_and_param,
    byte1_t params_value,
    arena_t *arena,
    process_data_t *process)
{
    param_type_t type = type_and_param->type;
    parameter_t param = type_and_param->param;

    if (!(params_value & type))
        return 1l << 32;
    if (params_value == PARAM_REG && param.reg < REG_NUMBER)
        return process->registers[param.reg];
    if (params_value == PARAM_DIR)
        return param.dir;
    if (params_value == PARAM_IND)
        return arena->memory[process->pc + param.ind % IDX_MOD];
    if (params_value & PARAM_INDEX)
        return arena->memory[process->pc + param.index % IDX_MOD];
    if (params_value & PARAM_DIRDEX)
        return param.index;
    return 1l << 32;
}

sbyte8_t get_data_in_param(
    type_and_param_t *type_and_param,
    byte1_t params_value,
    arena_t *arena,
    process_data_t *process)
{
    param_type_t type = type_and_param->type;
    parameter_t param = type_and_param->param;

    if (!(params_value & type))
        return 1l << 32;
    if (type == PARAM_REG && param.reg < REG_NUMBER)
        return process->registers[param.reg];
    if (type == PARAM_DIR)
        return param.dir;
    if (type == PARAM_IND)
        return arena->memory[process->pc + param.ind];
    if (type & PARAM_INDEX)
        return arena->memory[process->pc + param.index];
    if (type & PARAM_DIRDEX)
        return param.index;
    return 1l << 32;
}
