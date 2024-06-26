#ifndef AUDIO_H
#define AUDIO_H
#include "config.h"
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    BOUNCE_1,
    BOUNCE_2,
    LASER_1,
    LASER_2,
    EXPLOSION_1,
    EXPLOSION_2,
    SHOOT_BALL,
    SLOW_BALL,
    EXPAND,
    ADDITION,
    DIVIDE,
    LEVEL_CHANGE,
    VICTORY,
    DEATH
} AUDIO_CHUNKS;

void init_mixer();
void load_assets();
void load_music(int level);
void play_music();
void free_mixer();
void pause_music();
void load_chunk(const char *filename, const AUDIO_CHUNKS chunk_name);
void play_chunk(AUDIO_CHUNKS chunk_name);
void play_bounce_chunk();
void play_laser_chunk();
void play_explosion_chunk();
#endif // AUDIO_H
