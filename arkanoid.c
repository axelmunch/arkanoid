#include "config.h"
#include "delta_time.h"
#include "entities/ball.h"
#include "entities/capsule.h"
#include "entities/entities_spawner.h"
#include "entities/entity.h"
#include "levels.h"
#include "math/collisions.h"
#include "score.h"
#include "text.h"
#include "textures.h"
#include "vaus.h"
#include "graphics.h"
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Window *pWindow = NULL;
SDL_Surface *win_surf = NULL;

bool multiplayer_mode = false;
bool cheat_key_press = false;
bool dead = false;

bool ball_collides_with_horizontal_border(const Ball *ball) {
    return ball->hit_box.origin.y < ball->hit_box.radius + GAME_BORDER_TOP;
}
bool ball_collides_with_vertical_border(const Ball *ball) {
    return (ball->hit_box.origin.x < ball->hit_box.radius + GAME_BORDER_X) ||
           (ball->hit_box.origin.x >
            (win_surf->w - GAME_BORDER_X - ball->hit_box.radius));
}

bool ball_collides_with_brick(const Ball *ball) {
    Level *level = get_level();
    const int offset_x = (win_surf->w - LEVEL_WIDTH * 32) / 2;
    for (int y = level->offset; y < level->height + level->offset; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            Brick brick = level->bricks[y][x];
            if (brick.type != EMPTY) {
                Rectangle brick_hitbox;
                brick_hitbox.origin.x = offset_x + x * BRICK_WIDTH;
                brick_hitbox.origin.y = LEVEL_OFFSET_Y + y * BRICK_HEIGHT;
                brick_hitbox.height = BRICK_HEIGHT;
                brick_hitbox.width = BRICK_WIDTH;
                if (rect_circle_collision(brick_hitbox, ball->hit_box)) {
                    // Animation
                    if (brick.type == METAL || brick.type == GOLD) {
                        brick.current_animation = 1;
                        brick.time_before_next_animation = ANIMATION_TIMER_MS;
                        level->bricks[y][x] = brick;
                    }

                    if (brick.type != GOLD) {
                        brick.durability--;
                    }

                    if (brick.durability == 0) {
                        if (brick.capsule_reward != CAPSULE_EMPTY) {
                            add_entity(create_entity(brick.capsule_reward,
                                                     brick_hitbox.origin));
                        }
                        break_brick(brick.type);
                        level->bricks[y][x] =
                            create_brick(EMPTY, CAPSULE_EMPTY);
                    } else {
                        level->bricks[y][x] = brick;
                    }

                    return true;
                }
            }
        }
    }
    return false;
}

bool ball_collides_with_entity(Ball *ball) {
    SpawnedEntities *entities = get_entities();
    for (int i = 0; i < entities->current_entities_count; i++) {
        if (rect_circle_collision(entities->entities[i].hit_box,
                                  ball->hit_box)) {
            if (entities->entities[i].type == HARMFUL) {
                explode_entity(i);
                add_score(150);
                return true;
            }
            if (entities->entities[i].type == MINI_VAUS) {
                return true;
            }
        }
    }
    return false;
}

void load_next() {
    dead = false;
    load_next_level();
    reset_spawner();
    reset_balls();
    reset_capsules();
    reset_vaus();
    Point ballPosition = {win_surf->w / 2, win_surf->h / 2};
    add_ball(create_ball(ballPosition));
    Balls *balls = get_balls();
    VAUS *vaus = get_vaus();
    catch_ball(&balls->spawned_balls[balls->current_balls_count - 1],
               vaus[0].hit_box, 0);
}

void init() {
    pWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);

    init_spawner();
    init_vaus(win_surf);
    init_score();
    load_next();
}

bool apply_ball_effect(double ball_direction, bool add_effect) {
    double margin = BALL_EFFECT * 1.5;

    if (add_effect) {
        if (ball_direction > 360 - margin ||
            (ball_direction < 180 && ball_direction > 180 - margin)) {
            return false;
        }

    } else {
        if (ball_direction < margin ||
            (ball_direction > 180 && ball_direction < 180 + margin)) {
            return false;
        }
    }

    return true;
}

void update_balls() {
    Balls *balls = get_balls();
    VAUS *vaus = get_vaus();
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        Vector ball_movement;
        rotate_by_angle(ball->velocity * get_delta_time_target(),
                        ball->direction, &ball_movement);
        ball->hit_box.origin.x += ball_movement.x;
        const bool collide_with_vaus_1_x =
            rect_circle_collision(vaus[0].hit_box, ball->hit_box);
        const bool collide_with_vaus_2_x =
            rect_circle_collision(vaus[1].hit_box, ball->hit_box);
        if (ball_collides_with_vertical_border(ball) || collide_with_vaus_1_x || (collide_with_vaus_2_x && multiplayer_mode) ||
            ball_collides_with_brick(ball) || ball_collides_with_entity(ball)) {
            ball->direction = fmod(180 - ball->direction, 360);
            ball->hit_box.origin.x -= ball_movement.x;
        }

        ball->hit_box.origin.y -= ball_movement.y;
        const bool collide_with_vaus_1_y =
            rect_circle_collision(vaus[0].hit_box, ball->hit_box);
        const bool collide_with_vaus_2_y =
            rect_circle_collision(vaus[1].hit_box, ball->hit_box);
        if (ball_collides_with_horizontal_border(ball) || collide_with_vaus_1_y || (collide_with_vaus_2_y && multiplayer_mode) ||
            ball_collides_with_brick(ball) || ball_collides_with_entity(ball)) {
            ball->direction = fmod(360 - ball->direction, 360);
            ball->hit_box.origin.y += ball_movement.y;
        }
        if (collide_with_vaus_1_x || collide_with_vaus_1_y) {
            if (vaus[0].moving_direction == LEFT) {
                if (apply_ball_effect(ball->direction, true)) {
                    ball->direction = fmod(ball->direction + BALL_EFFECT, 360);
                }
            } else if (vaus[0].moving_direction == RIGHT) {
                if (apply_ball_effect(ball->direction, false)) {
                    ball->direction = fmod(ball->direction - BALL_EFFECT, 360);
                }
            }
            if (get_active_capsule() == CAPSULE_CATCH) {
                catch_ball(ball, vaus[0].hit_box, 0);
            }
        }
        if ((collide_with_vaus_2_x || collide_with_vaus_2_y) && multiplayer_mode) {
            if (vaus[1].moving_direction == LEFT) {
                if (apply_ball_effect(ball->direction, true)) {
                    ball->direction = fmod(ball->direction + BALL_EFFECT, 360);
                }
            } else if (vaus[1].moving_direction == RIGHT) {
                if (apply_ball_effect(ball->direction, false)) {
                    ball->direction = fmod(ball->direction - BALL_EFFECT, 360);
                }
            }
            if (get_active_capsule() == CAPSULE_CATCH) {
                catch_ball(ball, vaus[1].hit_box, 1);
            }
        }

        if (ball->hit_box.origin.y - ball->hit_box.radius > win_surf->h) {
            remove_ball(i);
            if (balls->current_balls_count == 0) {
                dead = true;
            }
        }
    }
}

void update() {
    update_cooldowns();
    update_balls();
    update_spawner();
    if(update_entities(win_surf)){
        load_next();
    }
    if(update_level())
    {
        load_next();
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
        VAUS *vaus = get_vaus();
        vaus[0].moving_direction = NONE;
        vaus[1].moving_direction = NONE;
        if (keys[SDL_SCANCODE_LEFT]) {
            vaus[0].moving_direction = LEFT;
            move_VAUS(-10, 0);
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            vaus[0].moving_direction = RIGHT;
            move_VAUS(10, 0);
        }
        if (keys[SDL_SCANCODE_SPACE]) {
            if (!dead) {
                int mock, laser_height;
                get_texture_dimensions(EntityLaser_1, &mock, &mock, &mock,
                                       &laser_height);
                const Point shooting_origin = {
                        vaus[0].hit_box.origin.x + vaus[0].hit_box.width / 2,
                        vaus[0].hit_box.origin.y - laser_height};
                shoot(shooting_origin, 0);
            } else {
                reset_score();
                restart_level_1();
                load_next();
            }
        }
        
        if (keys[SDL_SCANCODE_1]) {
            if (!cheat_key_press && DEBUG_MODE) {
                cheat_key_press = true;
                apply_slow_capsule();
            }
        }
        else if(keys[SDL_SCANCODE_2]) {
            if (!cheat_key_press && DEBUG_MODE) {
                cheat_key_press = true;
                apply_catch_capsule();
            }
        }
        else if(keys[SDL_SCANCODE_3]) {
            if (!cheat_key_press && DEBUG_MODE) {
                cheat_key_press = true;
                apply_laser_capsule();
            }
        }
        else if(keys[SDL_SCANCODE_4]) {
            if (!cheat_key_press && DEBUG_MODE) {
                cheat_key_press = true;
                apply_expand_capsule(&vaus[0]);
                apply_expand_capsule(&vaus[1]);
            }
        }
        else if(keys[SDL_SCANCODE_5]) {
            if (!cheat_key_press && DEBUG_MODE) {
                cheat_key_press = true;
                apply_divide_capsule();
            }
        }
        else if(keys[SDL_SCANCODE_6]) {
            if (!cheat_key_press && DEBUG_MODE) {
                cheat_key_press = true;
                load_next();
            }
        }
        else if(keys[SDL_SCANCODE_7]) {
            if (!cheat_key_press && DEBUG_MODE) {
                cheat_key_press = true;
                apply_addition_capsule();
            }
        }
        else if(keys[SDL_SCANCODE_8]) {
            if (!cheat_key_press && DEBUG_MODE) {
                cheat_key_press = true;
                reset_score();
                restart_level_1();
                load_next();
            }
        }
        else {
            cheat_key_press = false;
        }

        if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_Q]) {
            multiplayer_mode = true;
            vaus[1].moving_direction = LEFT;
            move_VAUS(-10, 1);
        }
        if (keys[SDL_SCANCODE_D]) {
            multiplayer_mode = true;
            vaus[1].moving_direction = RIGHT;
            move_VAUS(10, 1);
        }
        if (keys[SDL_SCANCODE_LCTRL]) {
            if(multiplayer_mode) {
                if (!dead) {
                    int mock, laser_height;
                    get_texture_dimensions(EntityLaser_1, &mock, &mock, &mock,
                                           &laser_height);
                    const Point shooting_origin = {
                            vaus[1].hit_box.origin.x + vaus[1].hit_box.width / 2,
                            vaus[1].hit_box.origin.y - laser_height};
                    shoot(shooting_origin, 1);
                } else {
                    reset_score();
                    restart_level_1();
                    load_next();
                }
            }
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
        draw(win_surf, multiplayer_mode, dead);
        SDL_UpdateWindowSurface(pWindow);

        SDL_Delay((Uint32) GAME_FPS_MS);
    }

    SDL_Quit();
    return 0;
}
