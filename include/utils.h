#ifndef UTILS_H_
    #define UTILS_H_

    #include "structures.h"

void display_usage(void);

void print_robots_data(robot_info_t **robots, byte2_t robot_count);
void print_instruction_data(instruction_t *instruction);

unsigned int swap_endian(unsigned int num);
byte2_t update_program_counter(
    byte2_t program_counter,
    sbyte2_t n);

bool handle_a(corewar_data_t *data, const char **argv, int *i, int tmp);

#endif /* UTILS_H_ */
