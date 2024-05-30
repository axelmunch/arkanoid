#include "audio.h"

const char *assets_path = "assets";
Mix_Music *main_music;
Mix_Chunk *bounce_chunk;
Mix_Chunk *laser_chunk;

void init_mixer() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) <
        0) {
        printf("SDL_mixer could not initialize! %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(1);
    Mix_Volume(1, MIX_MAX_VOLUME);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
    load_assets();
}

void load_assets() {
    main_music = Mix_LoadMUS("assets/music.mp3");
    if (main_music == NULL) {
        printf("Failed to load music: %s\n", Mix_GetError());
    }

    load_chunk("bounce.ogg", &bounce_chunk);
}

void load_chunk(const char *chunk_name, Mix_Chunk **chunk) {
    char chunk_path[50];
    snprintf(chunk_path, sizeof(chunk_path), "%s/%s", assets_path, chunk_name);
    *chunk = Mix_LoadWAV(chunk_path);
    if (*chunk == NULL) {
        printf("Failed to load chunk %s: %s\n", chunk_name, Mix_GetError());
    }
}

void play_chunk(const int channel, const AUDIO chunk, const int loops) {
    if (Mix_PlayChannel(channel, get_chunk(chunk), loops) < 0) {
        printf("%s\n", Mix_GetError());
    }
}

void play_music() {
    if (Mix_PlayMusic(main_music, -1) < 0) {
        printf("Failed to play music: %s\n", Mix_GetError());
    }
}

Mix_Chunk *get_chunk(const AUDIO chunk_name) {
    switch (chunk_name) {
    case BOUNCE_C:
        return bounce_chunk;
    case LASER_C:
        return laser_chunk;
    }
    return NULL;
}

void free_mixer() {
    Mix_FreeMusic(main_music);
    Mix_FreeChunk(bounce_chunk);
    Mix_CloseAudio();
}