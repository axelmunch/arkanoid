#include "config.h"
#include "delta_time.h"
#include "entities/entity.h"
#include "levels.h"
#include "text.h"
#include "textures.h"
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

Ball ball;
VAUS vaus;

SDL_Window *pWindow = NULL;
SDL_Surface *win_surf = NULL;
SDL_Surface *plancheSprites = NULL;

void move_VAUS(double distance) {
    vaus.hit_box.origin.x += distance * get_delta_time_target();
    if (vaus.hit_box.origin.x < 0) {
        vaus.hit_box.origin.x = 0;
    } else if (vaus.hit_box.origin.x + vaus.hit_box.width > win_surf->w) {
        vaus.hit_box.origin.x = win_surf->w - vaus.hit_box.width;
    }
}

void init() {
    pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);
    plancheSprites = SDL_LoadBMP("./sprites.bmp");
    SDL_SetColorKey(plancheSprites, true, 0);

    load_level("levels/1.level");

    Point ballPosition = {win_surf->w / 2, win_surf->h / 2};
    ball = create_ball(ballPosition);
    Point vausPosition = {win_surf->w / 2, win_surf->h - 32};
    vaus = create_VAUS(vausPosition);
}

void draw_background() {
    Level *level = get_level();
    LevelTheme level_theme = level->theme;
    Textures theme_texture = BackgroundTheme1 + level_theme;
    int level_theme_position_ignore, level_theme_width, level_theme_height;
    get_texture_dimensions(theme_texture, &level_theme_position_ignore,
                           &level_theme_position_ignore, &level_theme_width,
                           &level_theme_height);
    for (int j = 0; j < win_surf->h; j += level_theme_height) {
        for (int i = 0; i < win_surf->w; i += level_theme_width) {
            draw_texture(win_surf, theme_texture, i, j, false);
        }
    }
}

void draw() {
    draw_background();

    draw_texture(win_surf, BallTexture, ball.hit_box.origin.x,
                 ball.hit_box.origin.y, true);

    Vector ball_movement;
    rotate_by_angle(ball.velocity * get_delta_time_target(), ball.direction,
                    &ball_movement);

    ball.hit_box.origin.x += ball_movement.x;
    if ((ball.hit_box.origin.x < ball.hit_box.radius) ||
        (ball.hit_box.origin.x > (win_surf->w - ball.hit_box.radius))) {
        ball.direction = fmod(180 - ball.direction, 360);
        ball.hit_box.origin.x -= ball_movement.x;
    }

    ball.hit_box.origin.y -= ball_movement.y;
    if ((ball.hit_box.origin.y < ball.hit_box.radius) ||
        (ball.hit_box.origin.y > (win_surf->h - ball.hit_box.radius))) {
        ball.direction = fmod(360 - ball.direction, 360);
        ball.hit_box.origin.y += ball_movement.y;
    }

    draw_vaus(win_surf, vaus);
    draw_text(win_surf, "Arkanoid", 10, 10);
    int fps_text_width = draw_text(win_surf, "FPS: ", 10, 40);
    draw_integer(win_surf, (int) get_current_fps(), 10 + fps_text_width, 40);

    Level *level = get_level();
    int offset_x = (win_surf->w - LEVEL_WIDTH * 32) / 2;
    int offset_y = 150;
    for (int y = level->offset; y < level->height + level->offset; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            if (level->bricks[y][x].type != EMPTY) {
                int brick_x = offset_x + x * 32;
                int brick_y = offset_y + y * 16;
                draw_brick(win_surf, level->bricks[y][x].type,
                           level->bricks[y][x].current_animation, brick_x,
                           brick_y);
            }
        }
    }
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
            move_VAUS(-10);
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            move_VAUS(10);
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
