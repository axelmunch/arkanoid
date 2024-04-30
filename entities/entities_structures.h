#ifndef ARKANOID_ENTITIES_STRUCTURES_H
#define ARKANOID_ENTITIES_STRUCTURES_H

#include "../math/math.h"

typedef struct AnimatedEntity AnimatedEntity;
typedef struct Ball Ball;
typedef struct VAUS VAUS;
typedef enum { HARMFUL, CAPSULE, LASER, EXPLOSION } EntityType;
typedef enum {
    CAPSULE_EMPTY,
    CAPSULE_SLOW,
    CAPSULE_CATCH,
    CAPSULE_LASER,
    CAPSULE_EXPAND,
    CAPSULE_DIVIDE,
    CAPSULE_BREAK,
    CAPSULE_ADDITION,
    HARMFUL_1,
    HARMFUL_2,
    HARMFUL_3,
    LASER_TYPE,
    LASER_EXPLOSION,
    EXPLOSION_TYPE
} SpecificType;
typedef enum {
    LEFT,
    RIGHT,
    NONE,
} HMovingDirection;

struct AnimatedEntity {
    int max_animation;
    int current_animation;
    int time_before_next_animation;
    double velocity;
    double direction;
    EntityType type;
    SpecificType specific_type;
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
    SpecificType active_powerup;
    HMovingDirection moving_direction;
};

#endif // ARKANOID_ENTITIES_STRUCTURES_H
