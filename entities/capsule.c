#include "capsule.h"

#include "entity.h"

SpecificType active_capsule = CAPSULE_EMPTY;
struct CatchedBall catched_ball;

void apply_expand_capsule(VAUS *vaus) {
    update_VAUS_size(vaus, vaus->expand_size + 1);
    update_active_capsule(CAPSULE_EXPAND);
}

void apply_slow_capsule() {
    Balls *balls = get_balls();
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        if (ball->velocity / 2 > 2) {
            ball->velocity /= 2;
        };
    }
    update_active_capsule(CAPSULE_SLOW);
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
void apply_capsule_catch() { update_active_capsule(CAPSULE_CATCH); }

void catch_ball(Ball *ball) {
    if (!catched_ball.catched) {
        ball->velocity = 0.0;
        ball->direction = 90;
        catched_ball.catched = true;
        catched_ball.ball = ball;
    }
}
void shoot() {
    if (active_capsule == CAPSULE_CATCH && catched_ball.catched) {
        catched_ball.ball->velocity = 7.0;
        catched_ball.catched = false;
    }
}
void update_active_capsule(SpecificType capsule_type) {
    bool capsule_twice = (active_capsule == capsule_type);
    if (!capsule_twice) {
        shoot();
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

SpecificType get_active_capsule() { return active_capsule; }
