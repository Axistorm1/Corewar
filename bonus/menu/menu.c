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
static Textures create_text(void)
{
    Textures asset = {0};

    asset.menu = LoadTexture("bonus/menu/assets/image.png");
    asset.pos_menu.x = 0.0f;
    asset.pos_menu.y = 0.0f;
    asset.title = LoadTexture("bonus/menu/assets/title.png");
    asset.pos_title.x = 580.0f;
    asset.pos_title.y = 140.0f;
    asset.start = LoadTexture("bonus/menu/assets/play.png");
    asset.pos_start.x = 810.0f;
    asset.pos_start.y = 450.0f;
    asset.setting = LoadTexture("bonus/menu/assets/Setting.png");
    asset.pos_setting.x = 810.0f;
    asset.pos_setting.y = 650.0f;
    asset.exit = LoadTexture("bonus/menu/assets/Exit.png");
    asset.pos_exit.x = 810.0f;
    asset.pos_exit.y = 850.0f;
    asset.mute = LoadTexture("bonus/menu/assets/mute.png");
    asset.pos_mute.x = 10.0f;
    asset.pos_mute.y = 10.0f;
    return asset;
}

int my_menu(void)
{
    SetTraceLogLevel(LOG_FATAL);
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
    asset = create_text();
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        switch (currentScreen)
        {
            case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                }
            } break;
            case GAMEPLAY:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(currentScreen)
            {
                case LOGO:
                {
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

                } break;
                case TITLE:
                {
                    DrawTexture(asset.menu, (int)asset.pos_menu.x, (int)asset.pos_menu.y, WHITE);
                    DrawTexture(asset.title, (int)asset.pos_title.x, (int)asset.pos_title.y, WHITE);
                    DrawTexture(asset.start, (int)asset.pos_start.x, (int)asset.pos_start.y, WHITE);
                    DrawTexture(asset.setting, (int)asset.pos_setting.x, (int)asset.pos_setting.y, WHITE);
                    DrawTexture(asset.exit, (int)asset.pos_exit.x, (int)asset.pos_exit.y, WHITE);
                    DrawTexture(asset.mute, (int)asset.pos_mute.x, (int)asset.pos_mute.y, WHITE);
                    if (is_hover(asset.start, asset.pos_start) == true) {
                        StopMusicStream(music);
                        EndDrawing();
                        CloseWindow();
                        return 1;
                    }
                    is_hover(asset.setting, asset.pos_setting);
                    if (is_hover(asset.exit, asset.pos_exit) == true) {
                        EndDrawing();
                        CloseWindow();
                        StopMusicStream(music);
                        return 0;
                    }
                    if (is_hover(asset.mute, asset.pos_mute)) {
                        if (is_music == 0) {
                            PauseMusicStream(music);
                            is_music = 1;
                         } else {
                            ResumeMusicStream(music);
                            is_music = 0;
                        }
                    }

                } break;
                case GAMEPLAY:
                {
                } break;
                case ENDING:
                {
                } break;
                default: break;
            }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
