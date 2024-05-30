#include "audio.h"

Mix_Music *main_music;
Mix_Chunk *bounce_chunk;

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
        printf("Failed to load main music: %s\n", Mix_GetError());
    }

    bounce_chunk = Mix_LoadWAV("assets/bounce.ogg");
    if (bounce_chunk == NULL) {
        printf("Failed to load bounce chunk: %s\n", Mix_GetError());
    }
}

void start_music() {
    if (Mix_PlayMusic(main_music, -1) < 0) {
        printf("Failed to play music: %s\n", Mix_GetError());
    }
}
void play_bounce_chunk() {
    if (Mix_PlayChannel(0, bounce_chunk, 0) < 0) {
        printf("%s\n", Mix_GetError());
    }
}

void stop_music() {
    Mix_FreeMusic(main_music);
    Mix_FreeChunk(bounce_chunk);
    Mix_CloseAudio();
}
