#include "ball.h"

Balls balls;

void add_ball(const Ball ball) {
    if (balls.current_balls_count >= MAX_ENTITIES) {
        return;
    }
    balls.spawned_balls[balls.current_balls_count] = ball;
    balls.current_balls_count++;
}

void remove_ball(int index) {
    balls.current_balls_count--;
    for (int i = index; i < balls.current_balls_count; i++) {
        balls.spawned_balls[i] = balls.spawned_balls[i + 1];
    }
}

void init_ball_shoot(const SDL_Surface *win_surf) {
    const Point ballPosition = {win_surf->w / 2, win_surf->h / 2};
    add_ball(create_ball(ballPosition));
    Balls *balls = get_balls();
    const VAUS *vaus = get_vaus();
    catch_ball(&balls->spawned_balls[balls->current_balls_count - 1],
               vaus[0].hit_box, 0);
}

void reset_balls() { balls.current_balls_count = 0; }

bool ball_collides_with_horizontal_border(const Ball *ball) {
    return ball->hit_box.origin.y < ball->hit_box.radius + GAME_BORDER_TOP;
}

bool ball_collides_with_vertical_border(SDL_Surface *win_surf,
                                        const Ball *ball) {
    return (ball->hit_box.origin.x < ball->hit_box.radius + GAME_BORDER_X) ||
           (ball->hit_box.origin.x >
            (win_surf->w - GAME_BORDER_X - ball->hit_box.radius));
}

bool ball_collides_with_brick(SDL_Surface *win_surf, const Ball *ball) {
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
                    play_chunk(BOUNCE);
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
                        score_break_brick(brick.type);
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

bool update_balls(SDL_Surface *win_surf, bool multiplayer_mode) {
    // Return false if no balls left

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
        if (ball_collides_with_vertical_border(win_surf, ball) ||
            collide_with_vaus_1_x ||
            (collide_with_vaus_2_x && multiplayer_mode) ||
            ball_collides_with_brick(win_surf, ball) ||
            ball_collides_with_entity(ball)) {
            ball->direction = fmod(180 - ball->direction, 360);
            ball->hit_box.origin.x -= ball_movement.x;
        }

        ball->hit_box.origin.y -= ball_movement.y;
        const bool collide_with_vaus_1_y =
            rect_circle_collision(vaus[0].hit_box, ball->hit_box);
        const bool collide_with_vaus_2_y =
            rect_circle_collision(vaus[1].hit_box, ball->hit_box);
        if (ball_collides_with_horizontal_border(ball) ||
            collide_with_vaus_1_y ||
            (collide_with_vaus_2_y && multiplayer_mode) ||
            ball_collides_with_brick(win_surf, ball) ||
            ball_collides_with_entity(ball)) {
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
        if ((collide_with_vaus_2_x || collide_with_vaus_2_y) &&
            multiplayer_mode) {
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
                return false;
            }
        }
    }

    return true;
}

Balls *get_balls() { return &balls; }
