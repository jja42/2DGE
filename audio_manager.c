#include "audio_manager.h"

Audio* init_audio(){
    Audio* audio = malloc(sizeof(Audio));
    //Handle Malloc Error
    if(audio == NULL){
         printf("Failed to allocate Config.\n");
         return NULL;
    }
    audio->audioJSON = read_json_into_objects("assets/config/audio.json");
    load_audio(audio);
    return audio;
}

void* load_sound_asset(const char* path) {
    return Mix_LoadWAV(path);
}

void* load_music_asset(const char* path) {
    return Mix_LoadMUS(path);
}

void load_audio(Audio* audio){
    list_t* sounds = json_list_get(audio->audioJSON,"sounds");

    load_asset_table((void**)audio->sounds,NUM_SOUNDS,sound_map,sounds,load_sound_asset,"sound");

    list_t* music = json_list_get(audio->audioJSON,"music");

    load_asset_table((void**)audio->music,NUM_MUSIC,music_map,music,load_music_asset,"music");
}

void play_sound(Mix_Chunk *sound,int loops,float volume,int channel)
{
    float Volume = 1;
    if (!sound)return;
    if (volume > 0)
    {
        Volume *= volume;
    }
    Mix_VolumeChunk(sound, (int)(Volume * MIX_MAX_VOLUME));
    Mix_PlayChannel(channel, sound, loops);
}

void play_music(Mix_Music* music, float volume){
    float Volume = 1;
    if (!music)return;
    if (volume > 0)
    {
        Volume *= volume;
    }
    Mix_VolumeMusic((int)(Volume * MIX_MAX_VOLUME));
    Mix_PlayMusic(music,-1);
}

void free_audio(Audio* audio)
{
    //free sounds
    for(int s = 0; s<NUM_SOUNDS; s++){
        if(audio->sounds[s]){
            Mix_FreeChunk(audio->sounds[s]);
            audio->sounds[s] = NULL;
        }
    }

    //free music
    for(int m = 0; m<NUM_MUSIC; m++){
        if(audio->music[m]){
            Mix_FreeMusic(audio->music[m]);
            audio->music[m] = NULL;
        }
    }

    //free list and json
    for(int i = 0; i<audio->audioJSON->capacity; i++){
        if(audio->audioJSON->data[i] != NULL){
            free_json(audio->audioJSON->data[i]);
        }
    }
    free_list(audio->audioJSON); 
}