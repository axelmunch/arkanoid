#ifndef AUDIO_H
#define AUDIO_H
#include "config.h"
#include <SDL2/SDL_mixer.h>

typedef enum {
    BOUNCE,
    LASER_1,
    LASER_2,
    EXPLOSION_1,
    EXPLOSION_2,
    SHOOT_BALL,
    SLOW_BALL,
    EXPAND,
    ADDITION,
    DIVIDE,
    BREAK,
} AUDIO_CHUNKS;

void init_mixer();
void load_assets();
void load_music(int level);
void play_music();
void free_mixer();
void load_chunk(const char *filename, const AUDIO_CHUNKS chunk_name);
void play_chunk(AUDIO_CHUNKS chunk_name);
void play_laser_chunk();
void play_explosion_chunk();
#endif // AUDIO_H
