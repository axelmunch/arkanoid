#ifndef AUDIO_H
#define AUDIO_H
#include "config.h"
#include <SDL2/SDL_mixer.h>

typedef enum {
    BOUNCE_C,
    POWER_UP_C,
    LASER_1_C,
    LASER_2_C,
    EXPLOSION_1_C,
    EXPLOSION_2_C,
    SHOOT_BALL_C,
} AUDIO;

void init_mixer();
void load_assets();
void load_music(const char *filename);
void play_music();
void free_mixer();
void load_chunk(const char *filename, const AUDIO chunk_name);
void play_chunk(AUDIO chunk_name);
void play_laser_chunk();
void play_explosion_chunk();
#endif // AUDIO_H
