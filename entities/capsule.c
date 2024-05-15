#include "capsule.h"

#include "entity.h"
void apply_expand_capsule(VAUS *vaus) {
    update_VAUS_size(vaus, vaus->expand_size + 1);
}

void apply_slow_capsule() {
    Balls *balls = get_balls();
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        if (ball->velocity / 2 > 2) {
            ball->velocity /= 2;
        };
    }
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
}
