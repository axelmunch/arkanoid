#include "audio.h"

const char *assets_path = "assets";
Mix_Music *main_music;
Mix_Chunk *chunks[CHUNK_COUNT];
int used_channel = 0;

void init_mixer() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) <
        0) {
        printf("SDL_mixer could not initialize! %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(CHANNEL_COUNT);
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        Mix_Volume(i, CHUNK_VOLUME);
    }
    Mix_VolumeMusic(MUSIC_VOLUME);
    load_assets();
}

void load_assets() {
    main_music = Mix_LoadMUS("assets/music.mp3");
    if (main_music == NULL) {
        printf("Failed to load music: %s\n", Mix_GetError());
    }

    load_chunk("bounce.ogg", BOUNCE_C);
    load_chunk("power_up.ogg", POWER_UP_C);
    load_chunk("laser1.ogg", LASER_1_C);
    load_chunk("laser2.ogg", LASER_2_C);
    load_chunk("explosion1.ogg", EXPLOSION_1_C);
    load_chunk("explosion2.ogg", EXPLOSION_2_C);
    load_chunk("shoot_ball.ogg", SHOOT_BALL_C);
}

void load_chunk(const char *chunk_filename, const AUDIO chunk_name) {
    char chunk_path[50];
    snprintf(chunk_path, sizeof(chunk_path), "%s/%s", assets_path,
             chunk_filename);
    chunks[chunk_name] = Mix_LoadWAV(chunk_path);
    if (chunks[chunk_name] == NULL) {
        printf("Failed to load chunk %s: %s\n", chunk_filename, Mix_GetError());
    }
}

void play_chunk(const AUDIO chunk_name) {
    if (Mix_PlayChannel(used_channel, chunks[chunk_name], 0) < 0) {
        printf("%s\n", Mix_GetError());
    }
    used_channel = (used_channel + 1) % 4;
}
void play_laser_chunk() {
    const uint8_t random_value = rand() % 2;
    if (random_value == 0) {
        play_chunk(LASER_1_C);
    } else {
        play_chunk(LASER_2_C);
    }
}
void play_explosion_chunk() {
    const uint8_t random_value = rand() % 2;
    if (random_value == 0) {
        play_chunk(EXPLOSION_1_C);
    } else {
        play_chunk(EXPLOSION_2_C);
    }
}

void play_music() {
    if (Mix_PlayMusic(main_music, -1) < 0) {
        printf("Failed to play music: %s\n", Mix_GetError());
    }
}

void free_mixer() {
    Mix_FreeMusic(main_music);
    for (int i = 0; i < CHUNK_COUNT; i++) {
        Mix_FreeChunk(chunks[i]);
    }
    Mix_CloseAudio();
}
