#include "config.h"
#include "delta_time.h"
#include "entities/entities_spawner.h"
#include "entities/entity.h"
#include "levels.h"
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

bool ball_collides_with_brick() {
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
                if (rect_circle_collision(brick_hitbox, ball.hit_box)) {
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

    load_level("levels/1.level");
    init_spawner();

    Point ballPosition = {win_surf->w / 2, win_surf->h / 2};
    ball = create_ball(ballPosition);
    Point vausPosition = {win_surf->w / 2, win_surf->h - 32};
    vaus = create_VAUS(vausPosition);
}

void draw_background() {
    Level *level = get_level();
    LevelTheme level_theme = level->theme;
    Textures theme_texture = BackgroundTheme1 + level_theme;
    int mock, level_theme_width, level_theme_height;
    get_texture_dimensions(theme_texture, &mock, &mock, &level_theme_width,
                           &level_theme_height);
    for (int j = 0; j < win_surf->h; j += level_theme_height) {
        for (int i = 0; i < win_surf->w; i += level_theme_width) {
            draw_texture(win_surf, theme_texture, i, j, false);
        }
    }
}

void draw_level() {
    const Level *level = get_level();
    const int offset_x = (win_surf->w - LEVEL_WIDTH * 32) / 2;
    for (int y = level->offset; y < level->height + level->offset; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            if (level->bricks[y][x].type != EMPTY) {
                int brick_x = offset_x + x * BRICK_WIDTH;
                int brick_y = LEVEL_OFFSET_Y + y * BRICK_HEIGHT;
                draw_brick(win_surf, level->bricks[y][x].type,
                           level->bricks[y][x].current_animation, brick_x,
                           brick_y);
            }
        }
    }
}

void draw_entities() {
    SpawnedEntities *entities = get_entities();
    for (int i = 0; i < entities->current_entitiesCount; i++) {
        draw_entity(win_surf, entities->entities[i]);
    }
}

void draw() {
    draw_background();

    draw_level();

    draw_vaus(win_surf, vaus);

    draw_texture(win_surf, BallTexture, ball.hit_box.origin.x,
                 ball.hit_box.origin.y, true);

    draw_entities();

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
    if (ball_collides_with_vertical_border() || collide_with_vaus_x ||
        ball_collides_with_brick()) {
        ball.direction = fmod(180 - ball.direction, 360);
        ball.hit_box.origin.x -= ball_movement.x;
    }

    ball.hit_box.origin.y -= ball_movement.y;
    const bool collide_with_vaus_y =
        rect_circle_collision(vaus.hit_box, ball.hit_box);
    if (ball_collides_with_horizontal_border() || collide_with_vaus_y ||
        ball_collides_with_brick()) {
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

void update_entities() {
    SpawnedEntities *entities = get_entities();
    for (int i = 0; i < entities->current_entitiesCount; i++) {
        AnimatedEntity *entity = &entities->entities[i];

        entity->time_before_next_animation -= get_delta_time() * 1000;
        if (entity->time_before_next_animation <= 0) {
            entity->time_before_next_animation = ANIMATION_TIMER_MS;
            entity->current_animation =
                fmod(entity->current_animation + 1, entity->max_animation);
        }

        if (entity->type == EXPLOSION) {
            if (entity->current_animation == entity->max_animation - 1) {
                remove_entity(i);
            }
            continue;
        }

        // Move
        Vector entity_movement;
        rotate_by_angle(entity->velocity * get_delta_time_target(),
                        entity->direction, &entity_movement);
        entity->hit_box.origin.x += entity_movement.x;
        entity->hit_box.origin.y -= entity_movement.y;

        if (entity->hit_box.origin.y > win_surf->h) {
            remove_entity(i);
            continue;
        }

        // Collision
        if (rect_circle_collision(entity->hit_box, ball.hit_box) ||
            rect_rect_collision(entity->hit_box, vaus.hit_box)) {
            if (entity->type == HARMFUL) {
                explode_entity(i);
            }
        }
    }
}

void update_level() {
    Level *level = get_level();
    for (int y = level->offset; y < level->height + level->offset; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            Brick brick = level->bricks[y][x];

            if (brick.type == METAL || brick.type == GOLD) {
                if (brick.current_animation > 0) {
                    brick.time_before_next_animation -= get_delta_time() * 1000;
                    if (brick.time_before_next_animation <= 0) {
                        brick.time_before_next_animation = ANIMATION_TIMER_MS;
                        brick.current_animation = fmod(
                            brick.current_animation + 1, brick.max_animation);
                    }
                }

                level->bricks[y][x] = brick;
            }
        }
    }
}

void update() {
    update_ball();
    update_spawner();
    update_entities();
    update_level();
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
