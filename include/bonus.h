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
    // THIS MUST BE A POWER OF 2
    // If not, the game will most certainly crash
    #define TOTAL_COLORS 16
    #define LIGHT_MODE_OFFSET TOTAL_COLORS * COLOR_WHITE

    //optimizations
    #define COLORS_MODULO 0xF
    #define COLORS_BS (unsigned int)__builtin_ctz(TOTAL_COLORS)

void launch_ncurses(void);
void run_ncurses(arena_t *arena, corewar_data_t *data);
void update_console_window(char *str, byte2_t prog_num, byte4_t cycle);
void exit_ncurses(void);

#endif /* BONUS_H_ */
