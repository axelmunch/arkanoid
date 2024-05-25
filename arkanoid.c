#include "config.h"
#include "delta_time.h"
#include "entities/capsule.h"
#include "entities/entities_spawner.h"
#include "entities/entity.h"
#include "levels.h"
#include "math/collisions.h"
#include "text.h"
#include "textures.h"

#include "entities/ball.h"
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

VAUS vaus;

SDL_Window *pWindow = NULL;
SDL_Surface *win_surf = NULL;
SDL_Surface *plancheSprites = NULL;

bool ball_collides_with_horizontal_border(const Ball *ball) {
    return (ball->hit_box.origin.y < ball->hit_box.radius + GAME_BORDER_TOP) ||
           (ball->hit_box.origin.y > (win_surf->h - ball->hit_box.radius));
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

bool laser_collides_with_brick(const AnimatedEntity *entity) {
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
                if (rect_rect_collision(brick_hitbox, entity->hit_box)) {
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

bool ball_collides_with_entity(Ball *ball) {
    SpawnedEntities *entities = get_entities();
    for (int i = 0; i < entities->current_entities_count; i++) {
        if (entities->entities[i].type == HARMFUL &&
            rect_circle_collision(entities->entities[i].hit_box,
                                  ball->hit_box)) {
            explode_entity(i);
            return true;
        }
    }
    return false;
}

void move_VAUS(double distance) {
    vaus.hit_box.origin.x += distance * get_delta_time_target();
    if (vaus.hit_box.origin.x < GAME_BORDER_X) {
        vaus.hit_box.origin.x = GAME_BORDER_X;
    } else if (vaus.hit_box.origin.x + vaus.hit_box.width >
               win_surf->w - GAME_BORDER_X) {
        vaus.hit_box.origin.x =
            win_surf->w - GAME_BORDER_X - vaus.hit_box.width;
    }

    Balls *balls = get_balls();
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        if (rect_circle_collision(vaus.hit_box, ball->hit_box)) {
            ball->hit_box.origin.x += distance * get_delta_time_target();
            if (ball_collides_with_vertical_border(ball)) {
                ball->hit_box.origin.x -= distance * get_delta_time_target();
                ball->hit_box.origin.y =
                    vaus.hit_box.origin.y - ball->hit_box.radius;
            }
        }
    }
    if (get_active_capsule() == CAPSULE_CATCH) {
        attach_ball_to_vaus(vaus.hit_box);
    }
}

void load_next() {
    load_next_level();
    init_spawner();
    Point ballPosition = {win_surf->w / 2, win_surf->h / 2};
    reset_balls();
    add_ball(create_ball(ballPosition));
    Point vausPosition = {win_surf->w / 2, win_surf->h - 32};
    vaus = create_VAUS(vausPosition);
}

void init() {
    pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);
    plancheSprites = SDL_LoadBMP("./sprites.bmp");
    SDL_SetColorKey(plancheSprites, true, 0);

    load_next();
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

    // Black background
    int black_background_width, black_background_height;
    get_texture_dimensions(BlackBackground, &mock, &mock,
                           &black_background_width, &black_background_height);
    for (int i = GAME_BORDER_X - black_background_width;
         i > -black_background_width; i -= 32) {
        for (int j = 0; j < win_surf->h; j += black_background_height) {
            draw_texture(win_surf, BlackBackground, i, j, false);
        }
    }
    for (int i = win_surf->w - GAME_BORDER_X; i < win_surf->w;
         i += black_background_width) {
        for (int j = 0; j < win_surf->h; j += black_background_height) {
            draw_texture(win_surf, BlackBackground, i, j, false);
        }
    }
    for (int i = GAME_BORDER_X; i < win_surf->w - GAME_BORDER_X;
         i += black_background_width) {
        for (int j = GAME_BORDER_TOP - black_background_height;
             j > -black_background_height; j -= black_background_height) {
            draw_texture(win_surf, BlackBackground, i, j, false);
        }
    }

    // Borders
    int border_side_width, border_side_height;
    get_texture_dimensions(BorderSide, &mock, &mock, &border_side_width,
                           &border_side_height);
    for (int i = GAME_BORDER_TOP; i < win_surf->h; i += border_side_height) {
        draw_texture(win_surf, BorderSide, GAME_BORDER_X - border_side_width, i,
                     false);
        draw_texture(win_surf, BorderSide, win_surf->w - GAME_BORDER_X, i,
                     false);
    }

    int border_top_width, border_top_height;
    get_texture_dimensions(BorderTop, &mock, &mock, &border_top_width,
                           &border_top_height);
    for (int i = GAME_BORDER_X;
         i < win_surf->w - GAME_BORDER_X - border_top_width;
         i += border_top_width) {
        draw_texture(win_surf, BorderTop, i,
                     GAME_BORDER_TOP - border_top_height, false);
    }
    draw_texture(win_surf, BorderTop,
                 win_surf->w - GAME_BORDER_X - border_top_width,
                 GAME_BORDER_TOP - border_top_height, false);

    int border_top_bigger_width, border_top_bigger_height;
    get_texture_dimensions(BorderTopBigger, &mock, &mock,
                           &border_top_bigger_width, &border_top_bigger_height);

    draw_texture(win_surf, BorderTopBigger,
                 win_surf->w / 3 - border_top_bigger_width / 2,
                 GAME_BORDER_TOP - border_top_bigger_height, false);
    draw_texture(win_surf, BorderTopBigger,
                 win_surf->w / 3 * 2 - border_top_bigger_width / 2,
                 GAME_BORDER_TOP - border_top_bigger_height, false);

    int border_corner_width, border_corner_height;
    get_texture_dimensions(BorderCornerLeft, &mock, &mock, &border_corner_width,
                           &border_corner_height);
    draw_texture(win_surf, BorderCornerLeft,
                 GAME_BORDER_X - border_corner_width,
                 GAME_BORDER_TOP - border_corner_height, false);
    draw_texture(win_surf, BorderCornerRight, win_surf->w - GAME_BORDER_X,
                 GAME_BORDER_TOP - border_corner_height, false);
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
    for (int i = 0; i < entities->current_entities_count; i++) {
        draw_entity(win_surf, entities->entities[i]);
    }
}

void draw() {
    draw_background();

    draw_level();

    draw_vaus(win_surf, vaus);

    Balls *balls = get_balls();
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        draw_texture(win_surf, BallTexture, ball->hit_box.origin.x,
                     ball->hit_box.origin.y, true);
    }

    draw_entities();

    draw_text(win_surf, "Arkanoid", 10, 10);
    int fps_text_width = draw_text(win_surf, "FPS: ", 10, 40);
    draw_integer(win_surf, (int) get_current_fps(), 10 + fps_text_width, 40);
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
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        Vector ball_movement;
        rotate_by_angle(ball->velocity * get_delta_time_target(),
                        ball->direction, &ball_movement);
        ball->hit_box.origin.x += ball_movement.x;
        const bool collide_with_vaus_x =
            rect_circle_collision(vaus.hit_box, ball->hit_box);
        if (ball_collides_with_vertical_border(ball) || collide_with_vaus_x ||
            ball_collides_with_brick(ball) || ball_collides_with_entity(ball)) {
            ball->direction = fmod(180 - ball->direction, 360);
            ball->hit_box.origin.x -= ball_movement.x;
        }

        ball->hit_box.origin.y -= ball_movement.y;
        const bool collide_with_vaus_y =
            rect_circle_collision(vaus.hit_box, ball->hit_box);
        if (ball_collides_with_horizontal_border(ball) || collide_with_vaus_y ||
            ball_collides_with_brick(ball) || ball_collides_with_entity(ball)) {
            ball->direction = fmod(360 - ball->direction, 360);
            ball->hit_box.origin.y += ball_movement.y;
        }
        if (collide_with_vaus_x || collide_with_vaus_y) {
            if (vaus.moving_direction == LEFT) {
                if (apply_ball_effect(ball->direction, true)) {
                    ball->direction = fmod(ball->direction + BALL_EFFECT, 360);
                }
            } else if (vaus.moving_direction == RIGHT) {
                if (apply_ball_effect(ball->direction, false)) {
                    ball->direction = fmod(ball->direction - BALL_EFFECT, 360);
                }
            }
            if (get_active_capsule() == CAPSULE_CATCH) {
                catch_ball(ball);
            }
        }
    }
}

void update_entities() {
    SpawnedEntities *entities = get_entities();
    for (int i = 0; i < entities->current_entities_count; i++) {
        AnimatedEntity *entity = &entities->entities[i];

        entity->time_before_next_animation -= get_delta_time() * 1000;
        if (entity->time_before_next_animation <= 0) {
            entity->time_before_next_animation = ANIMATION_TIMER_MS;
            entity->current_animation =
                fmod(entity->current_animation + 1, entity->max_animation);
        }

        if (entity->type == EXPLOSION ||
            entity->specific_type == LASER_EXPLOSION) {
            if (entity->current_animation == entity->max_animation - 1) {
                remove_entity(i);
            }
            continue;
        }

        // Change direction
        if (entity->type == HARMFUL) {
            entity->time_before_direction_change -= get_delta_time() * 1000;
            if (entity->time_before_direction_change <= 0) {
                entity->time_before_direction_change =
                    DIRECTION_CHANGE_TIMER_MS;
                entity->direction =
                    fmod(entity->direction + (rand() % 90) - 45, 360);
            }
        }

        // Move
        Vector entity_movement;
        rotate_by_angle(entity->velocity * get_delta_time_target(),
                        entity->direction, &entity_movement);
        if (entity->type == HARMFUL) {
            entity_movement.y -= get_delta_time() * 5;
        }
        if ((entity->hit_box.origin.x + entity_movement.x > GAME_BORDER_X &&
             entity->hit_box.origin.x + entity_movement.x +
                     entity->hit_box.width <
                 win_surf->w - GAME_BORDER_X) ||
            entity->type == CAPSULE) {
            entity->hit_box.origin.x += entity_movement.x;
        } else {
            entity->direction = fmod(entity->direction + 180, 360);
        }
        if (entity->hit_box.origin.y - entity_movement.y > GAME_BORDER_TOP ||
            entity->type == CAPSULE) {
            entity->hit_box.origin.y -= entity_movement.y;
        } else {
            if (entity->type == LASER) {
                remove_entity(i);
                continue;
            }
            entity->direction = fmod(entity->direction + 180, 360);
        }

        if (entity->hit_box.origin.y > win_surf->h) {
            remove_entity(i);
            continue;
        }

        // Collision
        if (entity->type == HARMFUL &&
            rect_rect_collision(entity->hit_box, vaus.hit_box)) {
            explode_entity(i);
        }
        if (entity->type == LASER) {
            if (laser_collides_with_brick(entity)) {
                add_entity(
                    create_entity(LASER_EXPLOSION, entity->hit_box.origin));
                remove_entity(i);
            }
        }

        // Capsules
        if (rect_rect_collision(entity->hit_box, vaus.hit_box)) {
            switch (entity->specific_type) {
            case CAPSULE_EXPAND:
                apply_expand_capsule(&vaus);
                break;
            case CAPSULE_SLOW:
                apply_slow_capsule();
                break;
            case CAPSULE_BREAK:
                load_next();
                break;
            case CAPSULE_DIVIDE:
                apply_divide_capsule();
                break;
            case CAPSULE_CATCH:
                update_active_capsule(CAPSULE_CATCH);
                attach_ball_to_vaus(vaus.hit_box);
                break;
            case CAPSULE_LASER:
                apply_laser_capsule();
                break;
            case CAPSULE_ADDITION:
                apply_addition_capsule();
                break;
            default:
                break;
            }
            remove_entity(i);
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
    if (is_level_completed()) {
        load_next();
    }
}

void update() {
    update_laser_reload_time();
    update_balls();
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
        if (keys[SDL_SCANCODE_SPACE]) {
            int mock, laser_height;
            get_texture_dimensions(EntityLaser_1, &mock, &mock, &mock,
                                   &laser_height);
            const Point shooting_origin = {
                vaus.hit_box.origin.x + vaus.hit_box.width / 2,
                vaus.hit_box.origin.y - laser_height};
            shoot(shooting_origin);
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
