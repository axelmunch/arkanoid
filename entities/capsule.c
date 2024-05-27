#include "capsule.h"

#include "entities_spawner.h"
#include "entity.h"

SpecificType active_capsule = CAPSULE_EMPTY;
uint8_t spawned_mini_vaus = 0;
float time_before_next_shoot = 0.0;
struct CatchedBall catched_ball;

void apply_expand_capsule(VAUS *vaus) {
    update_VAUS_size(vaus, vaus->expand_size + 1);
    update_active_capsule(CAPSULE_EXPAND);
}

void update_balls_velocity(float velocity) {
    Balls *balls = get_balls();
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        if (velocity > 2.0) {
            ball->velocity = velocity;
        }
    }
}
void apply_slow_capsule() {
    update_active_capsule(CAPSULE_SLOW);
    update_balls_velocity(BALL_SPEED / 2);
}
void apply_divide_capsule() {
    Ball originBall = get_balls()->spawned_balls[0];
    Ball ball_one = create_ball(originBall.hit_box.origin);
    ball_one.direction = originBall.direction + 5;
    ball_one.velocity = originBall.velocity;
    add_ball(ball_one);
    Ball ball_two = create_ball(originBall.hit_box.origin);
    ball_two.direction = originBall.direction - 5;
    ball_one.velocity = originBall.velocity;
    add_ball(ball_two);
    update_active_capsule(CAPSULE_DIVIDE);
}

void apply_addition_capsule() {
    int mock, mini_vaus_width, mini_vaus_height;
    get_texture_dimensions(EntityMiniVaus, &mock, &mock, &mini_vaus_width,
                           &mini_vaus_height);
    const int existing_mini_vaus_total_width =
        GAME_BORDER_X + mini_vaus_width * spawned_mini_vaus;
    if (existing_mini_vaus_total_width + mini_vaus_width <=
        SCREEN_WIDTH - GAME_BORDER_X) {
        const Point mini_vaus_position = {existing_mini_vaus_total_width,
                                          SCREEN_HEIGHT - mini_vaus_height};
        add_entity(create_entity(MINI_VAUS_TYPE, mini_vaus_position));
        spawned_mini_vaus++;
    }
}

void catch_ball(Ball *ball) {
    if (!catched_ball.catched) {
        ball->velocity = 0.0;
        ball->direction = 90;
        catched_ball.catched = true;
        catched_ball.ball = ball;
    }
}
void shoot_ball() {
    if (catched_ball.catched) {
        catched_ball.ball->velocity = 7.0;
        catched_ball.catched = false;
    }
}
void shoot_laser(const Point shoot_origin) {
    if (time_before_next_shoot <= 0) {
        AnimatedEntity laser = create_entity(LASER_TYPE, shoot_origin);
        laser.velocity = 15.0;
        laser.direction = 90;
        add_entity(laser);
        time_before_next_shoot = LASER_RELOAD_TIME_MS / 1000;
    }
}
void shoot(const Point shoot_origin) {
    if (active_capsule == CAPSULE_CATCH) {
        shoot_ball();
    } else if (active_capsule == CAPSULE_LASER) {
        shoot_laser(shoot_origin);
    }
}

void apply_laser_capsule() {
    time_before_next_shoot = 0.0;
    update_active_capsule(CAPSULE_LASER);
}

void update_active_capsule(SpecificType capsule_type) {
    bool capsule_twice = (active_capsule == capsule_type);
    if (!capsule_twice) {
        shoot_ball();
        update_balls_velocity(BALL_SPEED);
    }
    active_capsule = capsule_type;
}
void attach_ball_to_vaus(const Rectangle vaus_hitbox) {
    if (catched_ball.catched) {
        Point ball_position;
        ball_position.x = vaus_hitbox.origin.x + vaus_hitbox.width / 2;
        ball_position.y =
            vaus_hitbox.origin.y - catched_ball.ball->hit_box.radius;
        catched_ball.ball->hit_box.origin = ball_position;
    }
}
void reset_capsules() {
    active_capsule = CAPSULE_EMPTY;
    spawned_mini_vaus = 0;
    time_before_next_shoot = 0.0;
    catched_ball.catched = false;
}

void update_laser_reload_time() {
    if (get_active_capsule() == CAPSULE_LASER) {
        time_before_next_shoot -= get_delta_time();
    }
}

SpecificType get_active_capsule() { return active_capsule; }