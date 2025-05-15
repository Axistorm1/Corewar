/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** check_args.c
*/

#include <raylib.h>
#include "menu.h"
#include "my_string.h"
#include "my_stype.h"
#include "my_stdlib.h"
#include <stdlib.h>
#include "game_info.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

static bool is_click (Texture2D texture, Vector2 position)
{
    Rectangle bounds = {
        position.x,
        position.y,
        (float)texture.width,
        (float)texture.height
    };

    Vector2 mouse = GetMousePosition();
    bool hovering = CheckCollisionPointRec(mouse, bounds);

    return hovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

static bool is_hover (Texture2D texture, Vector2 position)
{

    Rectangle bounds = {
        position.x,
        position.y,
        (float)texture.width,
        (float)texture.height
    };

    Vector2 mouse = GetMousePosition();
    bool hovering = CheckCollisionPointRec(mouse, bounds);

    DrawTexture(texture, (int)position.x, (int)position.y, hovering ? GRAY : WHITE);
    return hovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

static textures_t create_settings(textures_t asset)
{
    asset.setting_data = malloc(sizeof(setting_t));
    asset.setting_data->button1 = true;
    asset.setting_data->is_click1 = false;
    asset.back = LoadTexture("bonus/menu/assets/back.png");
    asset.vec_data->pos_back.x = 1600.0f;
    asset.vec_data->pos_back.y = 50.0f;
    asset.tick_on = LoadTexture("bonus/menu/assets/tickbox_on.png");
    asset.vec_data->pos_tick_on.x = 725.0f;
    asset.vec_data->pos_tick_on.y = 450.0f;
    asset.swap = LoadTexture("bonus/menu/assets/swap.png");
    asset.vec_data->pos_swap.x = 725.0f;
    asset.vec_data->pos_swap.y = 515.0f;
    asset.select = LoadTexture("bonus/menu/assets/select.png");
    asset.vec_data->pos_select.x = 725.0f;
    asset.vec_data->pos_select.y = 560.0f;
    return asset;
}

static textures_t create_option(textures_t asset)
{
    asset.atom = LoadTexture("bonus/menu/assets/atom.png");
    asset.vec_data->pos_atom.x = 100.0f;
    asset.vec_data->pos_atom.y = 0.0f;
    asset.take = LoadTexture("bonus/menu/assets/take.png");
    asset.vec_data->pos_take_atom.x = 290.0f;
    asset.vec_data->pos_take_atom.y = 750.0f;
    asset.take_on = LoadTexture("bonus/menu/assets/take_on.png");
    asset.previous = LoadTexture("bonus/menu/assets/previous.png");
    asset.vec_data->pos_previous.x = 850.0f;
    asset.vec_data->pos_previous.y = 750.0f;
    asset.next = LoadTexture("bonus/menu/assets/next.png");
    asset.vec_data->pos_next.x = 1050.0f;
    asset.vec_data->pos_next.y = 750.0f;
    asset.john = LoadTexture("bonus/menu/assets/john.png");
    asset.vec_data->pos_john.x = 1050.0f;
    asset.vec_data->pos_john.y = 0.0f;
    asset.vec_data->pos_take_john.x = 1525.0f;
    asset.vec_data->pos_take_john.y = 750.0f;
    return asset;
}

static textures_t create_menu(void)
{
    textures_t asset = {0};
    asset.vec_data = malloc(sizeof(vector_t));
    asset.menu = LoadTexture("bonus/menu/assets/image.png");
    asset.vec_data->pos_menu.x = 0.0f;
    asset.vec_data->pos_menu.y = 0.0f;
    asset.title = LoadTexture("bonus/menu/assets/title.png");
    asset.vec_data->pos_title.x = 580.0f;
    asset.vec_data->pos_title.y = 140.0f;
    asset.start = LoadTexture("bonus/menu/assets/play.png");
    asset.vec_data->pos_start.x = 810.0f;
    asset.vec_data->pos_start.y = 450.0f;
    asset.setting = LoadTexture("bonus/menu/assets/Setting.png");
    asset.vec_data->pos_setting.x = 810.0f;
    asset.vec_data->pos_setting.y = 600.0f;
    asset.option = LoadTexture("bonus/menu/assets/options.png");
    asset.vec_data->pos_option.x = 810.0f;
    asset.vec_data->pos_option.y = 750.0f;
    asset.exit = LoadTexture("bonus/menu/assets/Exit.png");
    asset.vec_data->pos_exit.x = 810.0f;
    asset.vec_data->pos_exit.y = 900.0f;
    asset.mute = LoadTexture("bonus/menu/assets/mute.png");
    asset.vec_data->pos_mute.x = 10.0f;
    asset.vec_data->pos_mute.y = 10.0f;
    asset.sans = LoadTexture("bonus/menu/assets/Sans.png");
    asset.vec_data->pos_sans.x = 1000.0f;
    asset.vec_data->pos_sans.y = 500.0f;
    asset.enemy = LoadTexture("bonus/menu/assets/enemy.png");
    asset.vec_data->pos_enemy.x = -30.0f;
    asset.vec_data->pos_enemy.y = 200.0f;
    return asset;
}

static void select_music(textures_t *asset, game_info_t *game_data)
{
    Vector2 temp;
    if (is_hover(asset->swap, asset->vec_data->pos_swap) == true) {
        if (asset->setting_data->is_click1 == true)
            asset->setting_data->is_click1 = false;
        else
            asset->setting_data->is_click1 = true;
    }
    if (asset->setting_data->is_click1 == true) {
        DrawTexture(asset->select, (int)asset->vec_data->pos_select.x, (int)asset->vec_data->pos_select.y , WHITE);
        DrawTexture(asset->select, (int)asset->vec_data->pos_select.x, (int)asset->vec_data->pos_select.y + 40, WHITE);
        temp.x = asset->vec_data->pos_select.x;
        temp.y = asset->vec_data->pos_select.y;
        if (is_hover(asset->select, temp) == true)
            game_data->music_select = 0;
        temp.x = asset->vec_data->pos_select.x;
        temp.y = asset->vec_data->pos_select.y + 40;
        if (is_hover(asset->select, temp) == true)
            game_data->music_select = 1;
        DrawText("Terraria", (int)asset->vec_data->pos_select.x + 32, (int)asset->vec_data->pos_select.y + 12, 15, WHITE);
        DrawText("Undertale", (int)asset->vec_data->pos_select.x + 32, (int)asset->vec_data->pos_select.y + 52, 15, WHITE);
    }
}

int my_menu(game_info_t *game_data)
{
    SetTraceLogLevel(LOG_FATAL);
    int is_music = 0;

    game_data->abel = false;
    game_data->john = false;
    textures_t asset = {0};
    InitWindow(screenWidth, screenHeight, "corewar");
    game_screen_t currentScreen = TITLE;
    SetTargetFPS(60);
    InitAudioDevice();
    Music music = LoadMusicStream("bonus/menu/assets/menu_music.mp3");
    PlayMusicStream(music);
    ShowCursor();
    asset = create_menu();
    asset = create_settings(asset);
    asset = create_option(asset);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(asset.menu, (int)asset.vec_data->pos_menu.x, (int)asset.vec_data->pos_menu.y, WHITE);
        DrawTexture(asset.mute, (int)asset.vec_data->pos_mute.x, (int)asset.vec_data->pos_mute.y, WHITE);
        if (is_hover(asset.mute, asset.vec_data->pos_mute)) {
            if (is_music == 0) {
                PauseMusicStream(music);
                is_music = 1;
            } else {
                ResumeMusicStream(music);
                is_music = 0;
            }
        }
        switch(currentScreen) {
            case TITLE:
            {
                DrawTexture(asset.enemy, (int)asset.vec_data->pos_enemy.x, (int)asset.vec_data->pos_enemy.y, WHITE);
                DrawTexture(asset.title, (int)asset.vec_data->pos_title.x, (int)asset.vec_data->pos_title.y, WHITE);
                DrawTexture(asset.start, (int)asset.vec_data->pos_start.x, (int)asset.vec_data->pos_start.y, WHITE);
                DrawTexture(asset.setting, (int)asset.vec_data->pos_setting.x, (int)asset.vec_data->pos_setting.y, WHITE);
                DrawTexture(asset.option, (int)asset.vec_data->pos_option.x, (int)asset.vec_data->pos_option.y, WHITE);
                DrawTexture(asset.exit, (int)asset.vec_data->pos_exit.x, (int)asset.vec_data->pos_exit.y, WHITE);
                DrawTexture(asset.sans, (int)asset.vec_data->pos_sans.x, (int)asset.vec_data->pos_sans.y, WHITE);
                if (is_hover(asset.start, asset.vec_data->pos_start) == true) {
                    StopMusicStream(music);
                    EndDrawing();
                    CloseWindow();
                    return 1;
                }
                if (is_hover(asset.setting, asset.vec_data->pos_setting)) {
                        currentScreen = SETTING;
                        break;
                }
                if (is_hover(asset.option, asset.vec_data->pos_option)) {
                        currentScreen = OPTION;
                        break;
                }
                if (is_hover(asset.exit, asset.vec_data->pos_exit)) {
                    EndDrawing();
                    CloseWindow();
                    StopMusicStream(music);
                    return 0;
                }
            } break;
            case SETTING:
            {
                ClearBackground(RAYWHITE);
                DrawTexture(asset.enemy, (int)asset.vec_data->pos_enemy.x, (int)asset.vec_data->pos_enemy.y, WHITE);
                DrawTexture(asset.back, (int)asset.vec_data->pos_back.x, (int)asset.vec_data->pos_back.y, WHITE);
                DrawTexture(asset.tick_on, (int)asset.vec_data->pos_tick_on.x, (int)asset.vec_data->pos_tick_on.y, WHITE);
                DrawTexture(asset.swap, (int)asset.vec_data->pos_swap.x, (int)asset.vec_data->pos_swap.y, WHITE);
                if (asset.setting_data->button1 == false)
                    DrawText("White mode", 580, 455, 25, GREEN);
                if (asset.setting_data->button1 == true)
                    DrawText("White mode", 580, 455, 25, RED);
                game_data->light_mode = asset.setting_data->button1;
                DrawText("Game Music", 580, 520, 25, GRAY);
                select_music(&asset, game_data);
                if (is_hover(asset.back, asset.vec_data->pos_back)) {
                        currentScreen = TITLE;
                        break;
                }
                if (is_hover(asset.tick_on, asset.vec_data->pos_tick_on) || is_hover(asset.tick_off, asset.vec_data->pos_tick_off)) {
                        asset.setting_data->button1 = !asset.setting_data->button1;
                        break;
                }
                break;
            } break;
            case OPTION:
            {
                DrawTexture(asset.previous, (int)asset.vec_data->pos_previous.x, (int)asset.vec_data->pos_previous.y, WHITE);
                DrawTexture(asset.next, (int)asset.vec_data->pos_next.x, (int)asset.vec_data->pos_next.y, WHITE);
                DrawTexture(asset.john, (int)asset.vec_data->pos_john.x, (int)asset.vec_data->pos_john.y, WHITE);
                if (is_hover(asset.previous, asset.vec_data->pos_previous)) {
                    currentScreen = TITLE;
                    break;
                }
                is_hover(asset.next, asset.vec_data->pos_next);
                DrawTexture(asset.atom, (int)asset.vec_data->pos_atom.x, (int)asset.vec_data->pos_atom.y, WHITE);
                if (is_click(asset.take, asset.vec_data->pos_take_atom))
                    game_data->abel = !game_data->abel;
                if (game_data->abel == false)
                    DrawTexture(asset.take, (int)asset.vec_data->pos_take_atom.x, (int)asset.vec_data->pos_take_atom.y, WHITE);
                else
                    DrawTexture(asset.take_on, (int)asset.vec_data->pos_take_atom.x, (int)asset.vec_data->pos_take_atom.y, WHITE);
                if (is_click(asset.take, asset.vec_data->pos_take_john))
                    game_data->john = !game_data->john;
                if (game_data->john == false)
                    DrawTexture(asset.take, (int)asset.vec_data->pos_take_john.x, (int)asset.vec_data->pos_take_john.y, WHITE);
                else
                    DrawTexture(asset.take_on, (int)asset.vec_data->pos_take_john.x, (int)asset.vec_data->pos_take_john.y, WHITE);
                DrawText("         Abel\nThe best at being bad", 150, 620, 50, BLACK);
                DrawText("John_Snow\nBro is cold", 1450, 620, 50, BLACK);
            } break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
