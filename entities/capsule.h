#ifndef CAPSULE_H
#define CAPSULE_H
#include "ball.h"
#include "../config.h"
#include "entities_structures.h"
#include <SDL.h>

struct CatchedBall {
    Ball *ball;
    bool catched;
};

void apply_addition_capsule();
void apply_catch_capsule();
void apply_expand_capsule(SDL_Surface *win_surf, VAUS *vaus, int vaus_index);
void apply_slow_capsule();
void apply_divide_capsule();
void apply_laser_capsule();
void catch_ball(Ball *ball, Rectangle vaus_hit_box, int vaus_index);
void explode_mini_vaus();
void shoot(Point shoot_origin, int vaus_index);
void shoot_laser(Point shoot_origin, int vaus_index);
void shoot_ball(int vaus_index);
void update_active_capsule(SpecificType capsule_type);
void update_cooldowns();
void update_attached_ball(Rectangle vaus_hitbox, int vaus_index);
void reset_capsules();
SpecificType get_active_capsule();
#endif // CAPSULE_H
