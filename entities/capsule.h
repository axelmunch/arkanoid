#ifndef CAPSULE_H
#define CAPSULE_H
#include "ball.h"
#include "entities_structures.h"

struct CatchedBall {
    Ball *ball;
    bool catched;
};

void apply_expand_capsule(VAUS *vaus);
void apply_slow_capsule();
void apply_divide_capsule();
void apply_capsule_catch();
void catch_ball(Ball *ball);
void shoot();
void update_active_capsule(SpecificType capsule_type);
void attach_ball_to_vaus(Rectangle vaus_hitbox);
SpecificType get_active_capsule();
#endif // CAPSULE_H
