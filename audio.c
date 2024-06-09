#include "audio.h"

const char *assets_path = "assets";
Mix_Music *music;
Mix_Chunk *chunks[CHUNK_COUNT];
int used_channel = 0;

void init_mixer() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) <
        0) {
        printf("SDL_mixer could not initialize! %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(CHANNEL_COUNT);
    Mix_Volume(-1, CHUNK_VOLUME);
    Mix_VolumeMusic(MUSIC_VOLUME);
    load_assets();
}

void load_assets() {
    load_chunk("bounce", BOUNCE);
    load_chunk("divide", DIVIDE);
    load_chunk("laser1", LASER_1);
    load_chunk("laser2", LASER_2);
    load_chunk("explosion1", EXPLOSION_1);
    load_chunk("explosion2", EXPLOSION_2);
    load_chunk("shoot_ball", SHOOT_BALL);
    load_chunk("expand", EXPAND);
    load_chunk("addition", ADDITION);
    load_chunk("slow_ball", SLOW_BALL);
    load_chunk("break", LEVEL_CHANGE);
    load_chunk("victory", VICTORY);
}

void load_music(const int level) {
    Mix_FreeMusic(music);
    char path[50];
    snprintf(path, sizeof(path), "%s/music%d.ogg", assets_path, level);
    music = Mix_LoadMUS(path);
    if (music == NULL) {
        printf("Failed to load music: %s\n", Mix_GetError());
    } else {
        play_music();
    }
}

void pause_music() { Mix_HaltMusic(); }

void load_chunk(const char *filename, const AUDIO_CHUNKS chunk_name) {
    char chunk_path[50];
    snprintf(chunk_path, sizeof(chunk_path), "%s/%s.ogg", assets_path,
             filename);
    chunks[chunk_name] = Mix_LoadWAV(chunk_path);
    if (chunks[chunk_name] == NULL) {
        printf("Failed to load chunk %s: %s\n", filename, Mix_GetError());
    }
}

void play_chunk(const AUDIO_CHUNKS chunk_name) {
    if (Mix_PlayChannel(used_channel, chunks[chunk_name], 0) < 0) {
        printf("%s\n", Mix_GetError());
    }
    used_channel = (used_channel + 1) % CHANNEL_COUNT;
}
void play_laser_chunk() {
    const uint8_t random_value = rand() % 2;
    if (random_value == 0) {
        play_chunk(LASER_1);
    } else {
        play_chunk(LASER_2);
    }
}
void play_explosion_chunk() {
    const uint8_t random_value = rand() % 2;
    if (random_value == 0) {
        play_chunk(EXPLOSION_1);
    } else {
        play_chunk(EXPLOSION_2);
    }
}

void play_music() {
    if (Mix_PlayMusic(music, -1) < 0) {
        printf("Failed to play music: %s\n", Mix_GetError());
    }
}

void free_mixer() {
    Mix_FreeMusic(music);
    for (int i = 0; i < CHUNK_COUNT; i++) {
        Mix_FreeChunk(chunks[i]);
    }
    Mix_CloseAudio();
}
