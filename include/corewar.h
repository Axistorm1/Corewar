/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** corewar.h
*/


#ifndef COREWAR_H_
    #define COREWAR_H_

    #include "structures.h"

    #define UNUSED [[gnu::unused]]

    #ifndef BONUS_MODE
        #define BONUS_MODE 0
    #endif

    #define MAX_ROBOTS 1023
    #define MAX_CYCLES 4'733'960

corewar_data_t *check_args(int argc, const char **argv, corewar_data_t *data);
robot_info_t **distribute_robots(robot_info_t **robots, byte2_t robot_count);

#endif /* COREWAR_H_ */
