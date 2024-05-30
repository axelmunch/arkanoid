#ifndef AUDIO_H
#define AUDIO_H
#include <SDL2/SDL_mixer.h>

void init_mixer();
void load_assets();
void start_music();
void play_bounce_chunk();
void stop_music();
#endif // AUDIO_H
