#include "structures.h"
#include "utils.h"
#include <stdlib.h>

void *free_robots(robot_info_t **robots, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        free(robots[i]->filename);
        free(robots[i]->header);
        free(robots[i]->memory);
        free(robots[i]);
    }
    free(robots);
    return NULL;
}

void *free_corewar_data(corewar_data_t *data)
{
    free_robots(data->robots, data->robot_count);
    free(data);
    return NULL;
}
