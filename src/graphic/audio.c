#include "game_info.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void setup_audio(game_info_t *game_data)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music = NULL;
    if (game_data->music_select == 0)
        music = Mix_LoadMUS("src/graphic/menu/assets/terraria.mp3");
    else if (game_data->music_select == 1)
        music = Mix_LoadMUS("src/graphic/menu/assets/play_audio.mp3");
    else if (game_data->music_select == 2)
        music = Mix_LoadMUS("src/graphic/menu/assets/Doom.mp3");
    else
        music = Mix_LoadMUS("src/graphic/menu/assets/terraria.mp3");

    Mix_PlayMusic(music, 10);
}

void death_audio(void)
{
    Mix_Chunk *death = Mix_LoadWAV("src/graphic/menu/assets/death.mp3");
    Mix_PlayChannel(-1, death, 0);
}

void revive_audio(void)
{
    Mix_Chunk *revive = Mix_LoadWAV("src/graphic/menu/assets/revive.mp3");
    Mix_PlayChannel(-1, revive, 0);
}

void kill_audio(void)
{
    Mix_Chunk *revive = Mix_LoadWAV("src/graphic/menu/assets/kill.mp3");
    Mix_PlayChannel(-1, revive, 0);
}
