#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SDL2/SDL_mixer.h>
#include "asset_manager.h"

typedef enum {
    SOUND_JUMP,
    SOUND_SHOOT,
    SOUND_CLICK,
    NUM_SOUNDS
} SoundID;

typedef enum {
    MUSIC_MAIN,
    NUM_MUSIC
} MusicID;

static const NameMap sound_map[] = {
    { "jump", SOUND_JUMP },
    { "shoot", SOUND_SHOOT },
    { "click", SOUND_CLICK }
};

static const NameMap music_map[] = {
    { "main_bgm", MUSIC_MAIN },
};

typedef struct Audio{
    list_t* audioJSON;
    Mix_Chunk* sounds[NUM_SOUNDS];
    Mix_Music* music[NUM_MUSIC];
} Audio;

//initialize audio from JSON
Audio* init_audio();

//load audio files into sounds and music
void load_audio();

//define asset load for sounds
void* load_sound_asset(const char* path);

//define asset load for music
void* load_music_asset(const char* path);

//play a sound on a specified channel, at a specified volume and with a specified number of loops
void play_sound(Mix_Chunk *sound,int loops,float volume,int channel);

//play a music track at a specified volume, infinitely looping
void play_music(Mix_Music* music, float volume);

//free sounds, music, list and json
void free_audio(Audio* audio);

#endif