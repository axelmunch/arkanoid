#include "config.h"
#include "delta_time.h"
#include "entity.h"
#include "math/collisions.h"
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

bool ball_collides_with_horizontal_border() {
    return (ball.hit_box.origin.y < ball.hit_box.radius) ||
           (ball.hit_box.origin.y > (win_surf->h - ball.hit_box.radius));
}
bool ball_collides_with_vertical_border() {
    return (ball.hit_box.origin.x < ball.hit_box.radius) ||
           (ball.hit_box.origin.x > (win_surf->w - ball.hit_box.radius));
}

void move_VAUS(double distance) {
    vaus.hit_box.origin.x += distance * get_delta_time_target();
    if (vaus.hit_box.origin.x < 0) {
        vaus.hit_box.origin.x = 0;
    } else if (vaus.hit_box.origin.x + vaus.hit_box.width > win_surf->w) {
        vaus.hit_box.origin.x = win_surf->w - vaus.hit_box.width;
    }

    if (rect_circle_collision(vaus.hit_box, ball.hit_box)) {
        ball.hit_box.origin.x += distance * get_delta_time_target();
        if (ball_collides_with_vertical_border()) {
            ball.hit_box.origin.x -= distance * get_delta_time_target();
            ball.hit_box.origin.y = vaus.hit_box.origin.y - ball.hit_box.radius;
        }
    }
}

void init() {
    pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);
    plancheSprites = SDL_LoadBMP("./sprites.bmp");
    SDL_SetColorKey(plancheSprites, true, 0);

    Point ballPosition = {win_surf->w / 2, win_surf->h / 2};
    ball = create_ball(ballPosition);
    Point vausPosition = {win_surf->w / 2, win_surf->h - 32};
    vaus = create_VAUS(vausPosition);
}

void draw() {
    for (int j = 0; j < win_surf->h; j += 64) {
        for (int i = 0; i < win_surf->w; i += 48) {
            draw_texture(win_surf, BackgroundTile, i, j, false);
        }
    }

    draw_texture(win_surf, BallTexture, ball.hit_box.origin.x,
                 ball.hit_box.origin.y, true);
    draw_vaus(win_surf, vaus.hit_box.origin, vaus.expand_size);
    draw_text(win_surf, "Arkanoid", 10, 10);
    int fps_text_width = draw_text(win_surf, "FPS: ", 10, 40);
    draw_integer(win_surf, (int) get_current_fps(), 10 + fps_text_width, 40);
}

void update_ball() {
    Vector ball_movement;
    rotate_by_angle(ball.velocity * get_delta_time_target(), ball.direction,
                    &ball_movement);
    ball.hit_box.origin.x += ball_movement.x;
    const bool collide_with_vaus_x =
        rect_circle_collision(vaus.hit_box, ball.hit_box);
    if (ball_collides_with_vertical_border() || collide_with_vaus_x) {
        ball.direction = fmod(180 - ball.direction, 360);
        ball.hit_box.origin.x -= ball_movement.x;
    }

    ball.hit_box.origin.y -= ball_movement.y;
    const bool collide_with_vaus_y =
        rect_circle_collision(vaus.hit_box, ball.hit_box);
    if (ball_collides_with_horizontal_border() || collide_with_vaus_y) {
        ball.direction = fmod(360 - ball.direction, 360);
        ball.hit_box.origin.y += ball_movement.y;
    }

    if (collide_with_vaus_x || collide_with_vaus_y) {
        if (vaus.moving_direction == LEFT) {
            ball.direction = fmod(ball.direction + BALL_EFFECT, 360);
        } else if (vaus.moving_direction == RIGHT) {
            ball.direction = fmod(ball.direction - BALL_EFFECT, 360);
        }
    }
}
void update() { update_ball(); }
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
        vaus.moving_direction = NONE;
        if (keys[SDL_SCANCODE_LEFT]) {
            vaus.moving_direction = LEFT;
            move_VAUS(-10);
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            vaus.moving_direction = RIGHT;
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

        update();
        draw();
        SDL_UpdateWindowSurface(pWindow);

        SDL_Delay((Uint32) GAME_FPS_MS);
    }

    SDL_Quit();
    return 0;
}
