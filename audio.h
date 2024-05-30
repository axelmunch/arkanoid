#ifndef AUDIO_H
#define AUDIO_H
#include <SDL2/SDL_mixer.h>

typedef enum { LASER_C, BOUNCE_C } AUDIO;

void init_mixer();
void load_assets();
void play_music();
void free_mixer();
void load_chunk(const char *chunk_name, const Mix_Chunk *chunk);
void play_chunk(int channel, AUDIO chunk, int loops);
Mix_Chunk *get_chunk(AUDIO chunk_name);
#endif // AUDIO_H
