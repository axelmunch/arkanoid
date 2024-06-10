#include "capsule.h"

SpecificType active_capsule = CAPSULE_EMPTY;
uint8_t spawned_mini_vaus = 0;
float shoot_cooldown[2];
float catch_cooldown[2];
float balls_velocity = DEFAULT_BALL_VELOCITY;
struct CatchedBall catched_ball[2];

void apply_expand_capsule(SDL_Surface *win_surf, VAUS *vaus, int vaus_index) {
    if (update_VAUS_size(vaus, vaus->expand_size + 1)) {
        play_chunk(EXPAND);
    }
    if (vaus->hit_box.origin.x + vaus->hit_box.width >
        win_surf->w - GAME_BORDER_X) {
        vaus->hit_box.origin.x =
            win_surf->w - GAME_BORDER_X - vaus->hit_box.width;
    }
    update_attached_ball(vaus->hit_box, vaus_index);
}

void update_balls_velocity(float velocity) {
    if (velocity < 2) {
        velocity = 2;
    }
    balls_velocity = velocity;
    Balls *balls = get_balls();
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        ball->velocity = balls_velocity;
    }
}

void apply_slow_capsule() {
    update_active_capsule(CAPSULE_SLOW);
    update_balls_velocity(DEFAULT_BALL_VELOCITY / 1.5);
    play_chunk(SLOW_BALL);
}

void apply_divide_capsule() {
    Balls *balls = get_balls();
    if (balls->current_balls_count > 0) {
        Ball originBall = balls->spawned_balls[0];
        float direction = originBall.direction;

        // Shoot vertially if the ball is catched
        for (int i = 0; i < 2; i++) {
            if (catched_ball[i].catched &&
                catched_ball[i].ball->hit_box.origin.x ==
                    originBall.hit_box.origin.x &&
                catched_ball[i].ball->hit_box.origin.y ==
                    originBall.hit_box.origin.y) {
                direction = 90;
            }
        }

        Ball ball_one = create_ball(originBall.hit_box.origin);
        ball_one.direction = direction + 5;
        ball_one.velocity = balls_velocity;
        add_ball(ball_one);
        Ball ball_two = create_ball(originBall.hit_box.origin);
        ball_two.direction = direction - 5;
        ball_two.velocity = balls_velocity;
        add_ball(ball_two);
        play_chunk(DIVIDE);
    }
}
void apply_break_capsule(SDL_Surface *win_surf) { load_next_level(win_surf); }

void apply_addition_capsule() {
    int mock, mini_vaus_width, mini_vaus_height;
    get_texture_dimensions(EntityMiniVaus, &mock, &mock, &mini_vaus_width,
                           &mini_vaus_height);
    const int existing_mini_vaus_total_width =
        GAME_BORDER_X + mini_vaus_width * spawned_mini_vaus;
    if (existing_mini_vaus_total_width + mini_vaus_width <=
        SCREEN_WIDTH - GAME_BORDER_X) {
        const Point mini_vaus_position = {existing_mini_vaus_total_width,
                                          SCREEN_HEIGHT -
                                              mini_vaus_height * 2.5};
        AnimatedEntity mini_vaus =
            create_entity(MINI_VAUS_TYPE, mini_vaus_position);
        add_entity(mini_vaus);
        spawned_mini_vaus++;
        play_chunk(ADDITION);

        // Check if spawn in a ball
        Balls *balls = get_balls();
        for (int i = 0; i < balls->current_balls_count; i++) {
            Ball *ball = &balls->spawned_balls[i];
            if (rect_circle_collision(mini_vaus.hit_box, ball->hit_box)) {
                ball->hit_box.origin.y =
                    mini_vaus_position.y - ball->hit_box.radius;
            }
        }
    }
}
void apply_catch_capsule() {
    update_active_capsule(CAPSULE_CATCH);
    catch_cooldown[0] = 0;
    catch_cooldown[1] = 0;
}

void catch_ball(Ball *ball, const Rectangle vaus_hit_box, int vaus_index) {
    if (!catched_ball[vaus_index].catched && catch_cooldown[vaus_index] <= 0) {
        if (catched_ball[1 - vaus_index].catched &&
            catched_ball[1 - vaus_index].ball == ball) {
            return;
        }
        ball->velocity = 0.0;
        catched_ball[vaus_index].catched = true;
        catched_ball[vaus_index].ball = ball;
        update_attached_ball(vaus_hit_box, vaus_index);
    }
}

void shoot_ball(int vaus_index) {
    if (catched_ball[vaus_index].catched) {
        catched_ball[vaus_index].ball->velocity = DEFAULT_BALL_VELOCITY;
        catched_ball[vaus_index].ball->direction = 90;
        catched_ball[vaus_index].catched = false;
        catch_cooldown[vaus_index] = CATCH_BALL_RELOAD_TIME_MS;
        shoot_cooldown[vaus_index] = SHOOT_RELOAD_TIME_MS;
        play_chunk(SHOOT_BALL);
    }
}

void shoot_laser(const Point shoot_origin, const int vaus_index) {
    int mock, laser_width;
    get_texture_dimensions(EntityLaser_1, &mock, &mock, &laser_width, &mock);
    AnimatedEntity left_laser = create_entity(LASER_TYPE, shoot_origin);
    left_laser.velocity = 15.0;
    left_laser.direction = 90;
    left_laser.hit_box.origin.x -= laser_width * 1.5;
    add_entity(left_laser);
    AnimatedEntity right_laser = create_entity(LASER_TYPE, shoot_origin);
    right_laser.velocity = 15.0;
    right_laser.direction = 90;
    right_laser.hit_box.origin.x += laser_width * 0.5;
    add_entity(right_laser);
    shoot_cooldown[vaus_index] = SHOOT_RELOAD_TIME_MS;
    play_laser_chunk();
}

void shoot(const Point shoot_origin, int vaus_index) {
    if (shoot_cooldown[vaus_index] <= 0) {
        if (active_capsule == CAPSULE_LASER) {
            shoot_laser(shoot_origin, vaus_index);
        } else {
            shoot_ball(vaus_index);
        }
    }
}

void apply_laser_capsule() { update_active_capsule(CAPSULE_LASER); }

void update_active_capsule(SpecificType capsule_type) {
    bool capsule_twice = (active_capsule == capsule_type);
    if (!capsule_twice) {
        shoot_ball(0);
        shoot_ball(1);
        update_balls_velocity(DEFAULT_BALL_VELOCITY);
    }
    active_capsule = capsule_type;
}

void update_attached_ball(const Rectangle vaus_hitbox, int vaus_index) {
    if (catched_ball[vaus_index].catched) {
        Point ball_position;
        ball_position.x = vaus_hitbox.origin.x + vaus_hitbox.width / 2;
        ball_position.y = vaus_hitbox.origin.y -
                          catched_ball[vaus_index].ball->hit_box.radius;
        catched_ball[vaus_index].ball->hit_box.origin = ball_position;
    }
}

void reset_capsules() {
    update_active_capsule(CAPSULE_EMPTY);
    spawned_mini_vaus = 0;
    shoot_cooldown[0] = 200;
    shoot_cooldown[1] = 200;
    catch_cooldown[0] = 0;
    catch_cooldown[1] = 0;
    balls_velocity = DEFAULT_BALL_VELOCITY;
    catched_ball[0].catched = false;
    catched_ball[1].catched = false;
}

void update_cooldowns() {
    shoot_cooldown[0] -= get_delta_time() * 1000;
    shoot_cooldown[1] -= get_delta_time() * 1000;
    catch_cooldown[0] -= get_delta_time() * 1000;
    catch_cooldown[1] -= get_delta_time() * 1000;
}

SpecificType get_active_capsule() { return active_capsule; }
