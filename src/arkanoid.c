#define SDL_MAIN_HANDLED
#include "audio.h"
#include "config.h"
#include "delta_time.h"
#include "entities/ball.h"
#include "entities/capsule.h"
#include "entities/entities_spawner.h"
#include "entities/entity.h"
#include "graphics.h"
#include "levels.h"
#include "score.h"
#include "text.h"
#include "textures.h"
#include "vaus.h"
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

SDL_Window *pWindow = NULL;
SDL_Surface *win_surf = NULL;

bool game_paused = false;
bool game_paused_press = false;
bool cheat_key_press = false;
bool multiplayer_mode = false;
int lives = DEFAULT_LIVES;

void init_icon(void) {
    char icon_path[20];
    sprintf(icon_path, "%s/icon.bmp", ASSETS_PATH);
    SDL_Surface *icon = SDL_LoadBMP(icon_path);
    SDL_SetColorKey(icon, true, 0);
    SDL_SetWindowIcon(pWindow, icon);
    SDL_FreeSurface(icon);
}

void init() {
    pWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);
    init_icon();
    init_mixer();
    init_spawner();
    init_vaus(win_surf);
    init_score();
    load_next_level(win_surf);
    init_delta_time();
    init_text();
    init_texture();
}

void update() {
    update_cooldowns();
    if (!update_balls(win_surf, multiplayer_mode)) {
        lives--;
        if (lives > 0) {
            reset_capsules();
            init_ball_shoot(win_surf);
        } else {
            pause_music();
            play_chunk(DEATH);
        }
    }
    update_spawner();
    update_entities(win_surf, multiplayer_mode);
    const bool level_complete = update_level();
    if (level_complete) {
        load_next_level(win_surf);
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    }

    init();

    bool quit = false;
    while (!quit) {
        update_delta_time();

        SDL_PumpEvents();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        VAUS *vaus = get_vaus();
        vaus[0].moving_direction = NONE;
        vaus[1].moving_direction = NONE;
        if (!is_end_game() && !game_paused && lives > 0) {
            if (keys[SDL_SCANCODE_LEFT]) {
                vaus[0].moving_direction = LEFT;
                move_VAUS(-10, 0, multiplayer_mode);
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                vaus[0].moving_direction = RIGHT;
                move_VAUS(10, 0, multiplayer_mode);
            }
            if ((keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_Q])) {
                multiplayer_mode = true;
                vaus[1].moving_direction = LEFT;
                move_VAUS(-10, 1, multiplayer_mode);
            }
            if (keys[SDL_SCANCODE_D]) {
                multiplayer_mode = true;
                vaus[1].moving_direction = RIGHT;
                move_VAUS(10, 1, multiplayer_mode);
            }
            if (DEBUG_MODE) {
                if (keys[SDL_SCANCODE_1]) {
                    if (!cheat_key_press) {
                        cheat_key_press = true;
                        apply_slow_capsule();
                    }
                } else if (keys[SDL_SCANCODE_2]) {
                    if (!cheat_key_press) {
                        cheat_key_press = true;
                        apply_catch_capsule();
                    }
                } else if (keys[SDL_SCANCODE_3]) {
                    if (!cheat_key_press) {
                        cheat_key_press = true;
                        apply_laser_capsule();
                    }
                } else if (keys[SDL_SCANCODE_4]) {
                    if (!cheat_key_press) {
                        cheat_key_press = true;
                        apply_expand_capsule(win_surf, &vaus[0], 0);
                        apply_expand_capsule(win_surf, &vaus[1], 1);
                    }
                } else if (keys[SDL_SCANCODE_5]) {
                    if (!cheat_key_press) {
                        cheat_key_press = true;
                        apply_divide_capsule();
                    }
                } else if (keys[SDL_SCANCODE_6]) {
                    if (!cheat_key_press) {
                        cheat_key_press = true;
                        apply_break_capsule(win_surf);
                    }
                } else if (keys[SDL_SCANCODE_7]) {
                    if (!cheat_key_press) {
                        cheat_key_press = true;
                        apply_addition_capsule();
                    }
                } else if (keys[SDL_SCANCODE_8]) {
                    if (!cheat_key_press) {
                        cheat_key_press = true;
                        multiplayer_mode = false;
                        reset_score();
                        restart_level_1(win_surf);
                        lives = DEFAULT_LIVES;
                        game_paused = false;
                    }
                } else {
                    cheat_key_press = false;
                }

                if (keys[SDL_SCANCODE_9]) {
                    set_time_scale(0.5);
                } else {
                    set_time_scale(1.0);
                }
            }
        }

        if (keys[SDL_SCANCODE_SPACE]) {
            if (lives > 0 && !is_end_game()) {
                if (!game_paused) {
                    int mock, laser_height;
                    get_texture_dimensions(EntityLaser_1, &mock, &mock, &mock,
                                           &laser_height);
                    const Point shooting_origin = {
                        vaus[0].hit_box.origin.x + vaus[0].hit_box.width / 2,
                        vaus[0].hit_box.origin.y - laser_height};
                    shoot(shooting_origin, 0);
                }
            } else {
                multiplayer_mode = false;
                reset_score();
                restart_level_1(win_surf);
                lives = DEFAULT_LIVES;
                game_paused = false;
            }
        }
        if (keys[SDL_SCANCODE_LCTRL]) {
            if (multiplayer_mode) {
                if (lives > 0 && !is_end_game() && !game_paused) {
                    int mock, laser_height;
                    get_texture_dimensions(EntityLaser_1, &mock, &mock, &mock,
                                           &laser_height);
                    const Point shooting_origin = {
                        vaus[1].hit_box.origin.x + vaus[1].hit_box.width / 2,
                        vaus[1].hit_box.origin.y - laser_height};
                    shoot(shooting_origin, 1);
                }
            }
        }

        if (keys[SDL_SCANCODE_P]) {
            if (!game_paused_press && !is_end_game() && lives > 0) {
                game_paused_press = true;
                game_paused = !game_paused;
            }
        } else {
            game_paused_press = false;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                reset_score();
                quit = true;
                break;
            case SDL_KEYUP:
                int key = event.key.keysym.sym;
                if (key == SDLK_ESCAPE) {
                    reset_score();
                    quit = true;
                    break;
                }
            }
        }

        if (!is_end_game() && lives > 0 && !game_paused) {
            update();
        }
        draw(win_surf, multiplayer_mode, lives, game_paused);
        SDL_UpdateWindowSurface(pWindow);

        SDL_Delay((Uint32) GAME_FPS_MS);
    }
    free_mixer();
    SDL_Quit();
    return 0;
}
