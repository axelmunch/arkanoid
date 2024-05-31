#ifndef AUDIO_H
#define AUDIO_H
#include "config.h"
#include <SDL2/SDL_mixer.h>

typedef enum { LASER_C, BOUNCE_C, POWER_UP_C } AUDIO;

void init_mixer();
void load_assets();
void play_music();
void free_mixer();
void load_chunk(const char *chunk_filename, const AUDIO chunk_name);
void play_chunk(AUDIO chunk_name);
#endif // AUDIO_H
