/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** menu.h
*/

#ifndef MENU_H_
    #define MENU_H_

    #include "raylib.h"

typedef enum game_screen_e {
    TITLE,
    SETTING,
    OPTION
} game_screen_t;

typedef struct vector_s {
    Vector2 pos_menu;
    Vector2 pos_title;
    Vector2 pos_start;
    Vector2 pos_setting;
    Vector2 pos_exit;
    Vector2 pos_mute;
    Vector2 pos_sans;
    Vector2 pos_back;
    Vector2 pos_tick_on;
    Vector2 pos_tick_off;
    Vector2 pos_swap;
    Vector2 pos_enemy;
    Vector2 pos_select;
    Vector2 pos_option;
    Vector2 pos_atom;
    Vector2 pos_take_atom;
    Vector2 pos_take_john;
    Vector2 pos_previous;
    Vector2 pos_next;
    Vector2 pos_john;
} vector_t;

typedef struct setting_s {
    bool button1;
    bool is_click1;
} setting_t;

typedef struct textures_s {
    vector_t *vec_data;
    setting_t *setting_data;
    Texture2D menu;
    Texture2D title;
    Texture2D start;
    Texture2D setting;
    Texture2D option;
    Texture2D exit;
    Texture2D mute;
    Texture2D sans;
    Texture2D back;
    Texture2D tick_on;
    Texture2D tick_off;
    Texture2D swap;
    Texture2D enemy;
    Texture2D select;
    Texture2D atom;
    Texture2D take;
    Texture2D take_on;
    Texture2D previous;
    Texture2D next;
    Texture2D john;
} textures_t;

#endif /* MENU_H_ */
