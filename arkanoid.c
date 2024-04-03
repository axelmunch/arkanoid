#include "config.h"
#include "delta_time.h"
#include "entity.h"
#include "text.h"
#include "textures.h"
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

Ball ball;
double x_vault;

SDL_Window *pWindow = NULL;
SDL_Surface *win_surf = NULL;
SDL_Surface *plancheSprites = NULL;

void init() {
    pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);
    plancheSprites = SDL_LoadBMP("./sprites.bmp");
    SDL_SetColorKey(plancheSprites, true, 0);

    Point ballPosition = {win_surf->w / 2, win_surf->h / 2};
    ball = createBall(ballPosition);
}

void draw() {
    for (int j = 0; j < win_surf->h; j += 64) {
        for (int i = 0; i < win_surf->w; i += 48) {
            draw_texture(win_surf, BackgroundTile, i, j, false);
        }
    }

    draw_texture(win_surf, BallTexture, ball.hit_box.origin.x,
                 ball.hit_box.origin.y, true);

    Vector ball_movement;
    rotate_by_angle(ball.velocity * get_delta_time_target(), ball.direction,
                    &ball_movement);

    ball.hit_box.origin.x += ball_movement.x;
    if ((ball.hit_box.origin.x < ball.hit_box.radius) ||
        (ball.hit_box.origin.x > (win_surf->w - ball.hit_box.radius))) {
        ball.direction += 90;
        ball.hit_box.origin.x -= ball_movement.x;
    }

    ball.hit_box.origin.y -= ball_movement.y;
    if ((ball.hit_box.origin.y < ball.hit_box.radius) ||
        (ball.hit_box.origin.y > (win_surf->h - ball.hit_box.radius))) {
        ball.direction += 90;
        ball.hit_box.origin.y += ball_movement.y;
    }

    draw_texture(win_surf, VausSize8, x_vault, win_surf->h - 32, false);

    draw_text(win_surf, "Arkanoid", 10, 10);
    int fps_text_width = draw_text(win_surf, "FPS: ", 10, 40);
    draw_integer(win_surf, (int) get_current_fps(), 10 + fps_text_width, 40);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    }

    init();
    init_delta_time();
    init_text();
    init_texture();

    bool quit = false;
    while (!quit) {
        update_delta_time();

        SDL_PumpEvents();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT]) {
            x_vault -= 10 * get_delta_time_target();
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            x_vault += 10 * get_delta_time_target();
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        draw();
        SDL_UpdateWindowSurface(pWindow);

        SDL_Delay((Uint32) GAME_FPS_MS);
    }

    SDL_Quit();
    return 0;
}
