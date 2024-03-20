#ifndef ARKANOID_ENTITY_H
#define ARKANOID_ENTITY_H

#include "math/math.h"
typedef enum { Harmful, Capsule } Type;

struct AnimatedEntity {
    int maxAnimation;
    int currentAnimation;
    int timeBeforeNextAnimation;
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
