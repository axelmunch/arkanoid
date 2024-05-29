#ifndef BALL_H
#define BALL_H
#include "../config.h"
#include "entities_structures.h"

typedef struct Balls Balls;
struct Balls {
    Ball spawned_balls[MAX_ENTITIES];
    int current_balls_count;
};

void add_ball(Ball ball);
void remove_ball(int index);
void reset_balls();
Balls *get_balls();

#endif // BALL_H
