#ifndef UTILS_H_
    #define UTILS_H_

    #include "structures.h"

void display_usage(void);

unsigned int swap_endian(unsigned int num);

byte2_t update_program_counter(
    byte2_t program_counter,
    sbyte2_t n);

bool handle_a(corewar_data_t *data, const char **argv, int *i, int tmp);

// free stuff
void *free_array(void **array, size_t size);
void *free_corewar_data(corewar_data_t *data);
void *free_robots(robot_info_t **robots, size_t count);

size_t str_array_len(char **array);

int my_str_isdigit(const char *str);

#endif /* UTILS_H_ */
