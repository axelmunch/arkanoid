#ifndef CAPSULE_H
#define CAPSULE_H
#include "ball.h"
#include "entities_structures.h"

struct CatchedBall {
    Ball *ball;
    bool catched;
};

void apply_addition_capsule();
void apply_expand_capsule(VAUS *vaus);
void apply_slow_capsule();
void apply_divide_capsule();
void apply_laser_capsule();
void catch_ball(Ball *ball);
void explode_mini_vaus();
void shoot(Point shoot_origin);
void shoot_laser(Point shoot_origin);
void shoot_ball();
void update_active_capsule(SpecificType capsule_type);
void update_laser_reload_time();
void attach_ball_to_vaus(Rectangle vaus_hitbox);
SpecificType get_active_capsule();
#endif // CAPSULE_H
