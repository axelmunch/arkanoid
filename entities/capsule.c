#include "capsule.h"

#include "entities_spawner.h"
#include "entity.h"

SpecificType active_capsule = CAPSULE_EMPTY;
uint8_t spawned_mini_vaus = 0;
float shoot_cooldown = 0.0;
float catch_cooldown = 0.0;
float balls_velocity = DEFAULT_BALL_VELOCITY;
struct CatchedBall catched_ball;

void apply_expand_capsule(VAUS *vaus) {
    update_VAUS_size(vaus, vaus->expand_size + 1);
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
    update_balls_velocity(DEFAULT_BALL_VELOCITY / 2);
}

void apply_divide_capsule() {
    Ball originBall = get_balls()->spawned_balls[0];
    Ball ball_one = create_ball(originBall.hit_box.origin);
    ball_one.direction = originBall.direction + 5;
    ball_one.velocity = balls_velocity;
    add_ball(ball_one);
    Ball ball_two = create_ball(originBall.hit_box.origin);
    ball_two.direction = originBall.direction - 5;
    ball_one.velocity = balls_velocity;
    add_ball(ball_two);
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
                                          SCREEN_HEIGHT -
                                              mini_vaus_height * 2.5};
        add_entity(create_entity(MINI_VAUS_TYPE, mini_vaus_position));
        spawned_mini_vaus++;
    }
}
void apply_catch_capsule() {
    update_active_capsule(CAPSULE_CATCH);
    catch_cooldown = 0.0;
}

void catch_ball(Ball *ball, const Rectangle vaus_hit_box) {
    if (!catched_ball.catched && catch_cooldown <= 0) {
        ball->velocity = 0.0;
        catched_ball.catched = true;
        catched_ball.ball = ball;
        update_attached_ball(vaus_hit_box);
    }
}
void shoot_ball() {
    if (catched_ball.catched) {
        catched_ball.ball->velocity = 7.0;
        catched_ball.ball->direction = 90;
        catched_ball.catched = false;
        catch_cooldown = CATCH_BALL_RELOAD_TIME_MS / 1000;
        shoot_cooldown = LASER_RELOAD_TIME_MS / 1000;
    }
}
void shoot_laser(const Point shoot_origin) {
    AnimatedEntity laser = create_entity(LASER_TYPE, shoot_origin);
    laser.velocity = 15.0;
    laser.direction = 90;
    add_entity(laser);
    shoot_cooldown = LASER_RELOAD_TIME_MS / 1000;
}
void shoot(const Point shoot_origin) {
    if (shoot_cooldown <= 0) {
        if (active_capsule == CAPSULE_LASER) {
            shoot_laser(shoot_origin);
        } else {
            shoot_ball();
        }
    }
}

void apply_laser_capsule() {
    shoot_cooldown = 0.0;
    update_active_capsule(CAPSULE_LASER);
}

void update_active_capsule(SpecificType capsule_type) {
    bool capsule_twice = (active_capsule == capsule_type);
    if (!capsule_twice) {
        shoot_ball();
        update_balls_velocity(DEFAULT_BALL_VELOCITY);
    }
    active_capsule = capsule_type;
}
void update_attached_ball(const Rectangle vaus_hitbox) {
    if (catched_ball.catched) {
        Point ball_position;
        ball_position.x = vaus_hitbox.origin.x + vaus_hitbox.width / 2;
        ball_position.y =
            vaus_hitbox.origin.y - catched_ball.ball->hit_box.radius;
        catched_ball.ball->hit_box.origin = ball_position;
    }
}

void reset_capsules() {
    update_active_capsule(CAPSULE_EMPTY);
    spawned_mini_vaus = 0;
    shoot_cooldown = 0.7; // 0.7s to prevent from shooting on restart right away
    catch_cooldown = 0.0;
    balls_velocity = DEFAULT_BALL_VELOCITY;
    catched_ball.catched = false;
}

void update_cooldowns() {
    shoot_cooldown -= get_delta_time();
    catch_cooldown -= get_delta_time();
}

SpecificType get_active_capsule() { return active_capsule; }
