/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** bonus.h
*/

#ifndef BONUS_H_
    #define BONUS_H_

    #include "structures.h"
    #include <ncurses.h>

    #define COLOR_ORANGE 8
    #define COLOR_DARK_RED 9
    #define TOTAL_COLORS 10

void launch_ncurses(void);
void run_ncurses(arena_t *arena, corewar_data_t *data);
void update_console_window(char *str, byte2_t prog_num);
void exit_ncurses(void);

#endif /* BONUS_H_ */
