
/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** menu.h
*/

#ifndef MENU_H_
    #define MENU_H_
    #include "raylib.h"



typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef struct {
    Texture2D menu;
    Vector2 pos_menu;
    Texture2D title;
    Vector2 pos_title;
    Texture2D start;
    Vector2 pos_start;
    Texture2D setting;
    Vector2 pos_setting;
    Texture2D exit;
    Vector2 pos_exit;
    Texture2D mute;
    Vector2 pos_mute;
} Textures;

#endif /* MENU_H_ */
