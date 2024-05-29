#include "audio.h"

Mix_Music *main_music;

void start_music() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) <
        0) {
        printf("SDL_mixer could not initialize! %s\n", Mix_GetError());
    }
    main_music = Mix_LoadMUS("assets/music.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    Mix_PlayMusic(main_music, -1);
}
void stop_music() {
    Mix_FreeMusic(main_music);
    Mix_CloseAudio();
}
