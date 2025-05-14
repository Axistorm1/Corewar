/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** check_args.c
*/

#include <raylib.h>
#include "menu.h"
#include "corewar.h"
#include "errors.h"
#include "op.h"
#include "structures.h"
#include "my_string.h"
#include "my_stype.h"
#include "my_stdlib.h"
#include <stdlib.h>

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

static Textures create_settings(Textures asset)
{
    asset.setting_data = malloc(sizeof(Setting));
    asset.setting_data->button1 = false;
    asset.back = LoadTexture("bonus/menu/assets/back.png");
    asset.vec_data->pos_back.x = 1600.0f;
    asset.vec_data->pos_back.y = 50.0f;
    asset.tick_on = LoadTexture("bonus/menu/assets/tickbox_on.png");
    asset.vec_data->pos_tick_on.x = 700.0f;
    asset.vec_data->pos_tick_on.y = 450.0f;
    asset.tick_off = LoadTexture("bonus/menu/assets/off.png");
    return asset;
}

static Textures create_menu(void)
{
    Textures asset = {0};
    asset.vec_data = malloc(sizeof(Vector));
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
    asset.vec_data->pos_setting.y = 650.0f;
    asset.exit = LoadTexture("bonus/menu/assets/Exit.png");
    asset.vec_data->pos_exit.x = 810.0f;
    asset.vec_data->pos_exit.y = 850.0f;
    asset.mute = LoadTexture("bonus/menu/assets/mute.png");
    asset.vec_data->pos_mute.x = 10.0f;
    asset.vec_data->pos_mute.y = 10.0f;
    asset.sans = LoadTexture("bonus/menu/assets/Sans.png");
    asset.vec_data->pos_sans.x = 1000.0f;
    asset.vec_data->pos_sans.y = 500.0f;
    return asset;
}

int my_menu(void)
{
    //SetTraceLogLevel(LOG_FATAL);
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int framesCounter = 0;
    int is_music = 0;
    Textures asset = {0};
    InitWindow(screenWidth, screenHeight, "example");
    GameScreen currentScreen = TITLE;
    SetTargetFPS(60);
    InitAudioDevice();
    Music music = LoadMusicStream("bonus/menu/assets/menu_music.mp3");
    PlayMusicStream(music);
    ShowCursor();
    asset = create_menu();
    asset = create_settings(asset);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(asset.menu, (int)asset.vec_data->pos_menu.x, (int)asset.vec_data->pos_menu.y, WHITE);
            DrawTexture(asset.mute, (int)asset.vec_data->pos_mute.x, (int)asset.vec_data->pos_mute.y, WHITE);
            switch(currentScreen)
            {
                case TITLE:
                {
                    DrawTexture(asset.title, (int)asset.vec_data->pos_title.x, (int)asset.vec_data->pos_title.y, WHITE);
                    DrawTexture(asset.start, (int)asset.vec_data->pos_start.x, (int)asset.vec_data->pos_start.y, WHITE);
                    DrawTexture(asset.setting, (int)asset.vec_data->pos_setting.x, (int)asset.vec_data->pos_setting.y, WHITE);
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
                    if (is_hover(asset.exit, asset.vec_data->pos_exit)) {
                        EndDrawing();
                        CloseWindow();
                        StopMusicStream(music);
                        return 0;
                    }
                    if (is_hover(asset.mute, asset.vec_data->pos_mute)) {
                        if (is_music == 0) {
                            PauseMusicStream(music);
                            is_music = 1;
                         } else {
                            ResumeMusicStream(music);
                            is_music = 0;
                        }
                    }

                } break;
                case SETTING:
                {
                    ClearBackground(RAYWHITE);
                    DrawTexture(asset.back, (int)asset.vec_data->pos_back.x, (int)asset.vec_data->pos_back.y, WHITE);
                    if (asset.setting_data->button1 == true) {
                        DrawTexture(asset.tick_on, (int)asset.vec_data->pos_tick_on.x, (int)asset.vec_data->pos_tick_on.y, WHITE);
                     } else {
                        printf("herree\n");
                        DrawTexture(asset.tick_off, (int)asset.vec_data->pos_tick_on.x, (int)asset.vec_data->pos_tick_on.y, WHITE);
                    }
                    DrawText("White mode", 580, 455, 20, GRAY);
                    if (is_hover(asset.back, asset.vec_data->pos_back)) {
                            currentScreen = TITLE;
                            break;
                    }
                    if (is_hover(asset.tick_on, asset.vec_data->pos_tick_on)) {
                            if (asset.setting_data->button1 == false) {
                                asset.setting_data->button1 = true;
                            } else {
                                asset.setting_data->button1 = false;
                            }
                            break;
                    }
                    break;
                }
            }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
