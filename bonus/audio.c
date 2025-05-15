/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** audio
*/


#include <raylib.h>
#include "corewar.h"
#include "errors.h"
#include "op.h"
#include "structures.h"
#include "my_string.h"
#include "my_stype.h"
#include "my_stdlib.h"
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "game_info.h"
void setup_audio(game_info *game_data)
{
      SDL_Init(SDL_INIT_AUDIO);
      Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
      Mix_Music *music;

      if (game_data->music_select == 1)
            music = Mix_LoadMUS("bonus/menu/assets/play_audio.mp3");
      if (game_data->music_select == 0)
            music = Mix_LoadMUS("bonus/menu/assets/terraria.mp3");
      Mix_PlayMusic(music, 1);
}
