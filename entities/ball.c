#include "ball.h"

#include <stddef.h>

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
void reset_balls() { balls.current_balls_count = 0; }
Balls *get_balls() { return &balls; }
