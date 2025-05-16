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
    #include "game_info.h"

    #define COLOR_ORANGE 8
    #define COLOR_DARK_RED 9
    // THIS MUST BE A POWER OF 2
    // If not, the game will most certainly crash
    #define TOTAL_COLORS 16
    #define LIGHT_MODE_OFFSET TOTAL_COLORS * COLOR_WHITE

    //optimizations
    #define COLORS_MODULO 0xF
    #define COLORS_BS (unsigned int)__builtin_ctz(TOTAL_COLORS)

void kill_audio(void);
void death_audio(void);
void revive_audio(void);
void launch_ncurses(game_info_t *game_info);
void run_ncurses(arena_t *arena, corewar_data_t *data);
void update_console_window(char *str, byte2_t prog_num, byte4_t cycle);
void exit_ncurses(void);
int my_menu(game_info_t *game_data);
void setup_audio(game_info_t *game_data);
instruction_t **parse_champions(header_t *header, char *filename);
char **transcribe_dot_s(instruction_t **instructions);
void add_raylib_champions(corewar_data_t *data, game_info_t *info);

#endif /* BONUS_H_ */
