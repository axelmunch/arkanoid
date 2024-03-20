#ifndef ARKANOID_ENTITY_H
#define ARKANOID_ENTITY_H

#include "math/math.h"
typedef enum { Harmful, Capsule } Type;

struct AnimatedEntity {
    int max_animation;
    int current_animation;
    int time_before_next_animation;
    double velocity;
    double direction;
    Type type;
    Rectangle hit_box;
};

struct Ball {
    double velocity;
    double direction;
    Circle hit_box;
};

struct VAUS {
    int expand_size;
    Rectangle hit_box;
};

#endif // ARKANOID_ENTITY_H
