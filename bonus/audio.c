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
void setup_audio(void)
{
      SDL_Init(SDL_INIT_AUDIO);
      Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
      Mix_Music *music = Mix_LoadMUS("bonus/menu/assets/play_audio.mp3");
      Mix_PlayMusic(music, 1);
}
