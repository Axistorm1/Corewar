#include "arena.h"
#include "op.h"
#include "structures.h"

sbyte8_t get_data_in_param(type_and_param_t *type_and_param,
                           byte1_t params_value, arena_t *arena,
                           process_data_t *process)
{
    param_type_t type  = type_and_param->type;
    parameter_t  param = type_and_param->param;

    if (!(params_value & type))
        return ERROR_VALUE;
    if (type == PARAM_REG && param.reg < REG_NUMBER)
        return process->registers[param.reg];
    if (type == PARAM_DIR)
        return param.dir;
    if (type == PARAM_IND)
        return arena->memory[(process->pc + param.ind) % MEM_SIZE];
    if (type & PARAM_INDEX)
        return arena->memory[(process->pc + param.index) % MEM_SIZE];
    if (type & PARAM_DIRDEX)
        return param.index;
    return ERROR_VALUE;
}
