#ifndef ARKANOID_ENTITY_H
#define ARKANOID_ENTITY_H

#include "config.h"
#include "math/math.h"
#include "textures.h"

typedef struct AnimatedEntity AnimatedEntity;
typedef struct Ball Ball;
typedef struct VAUS VAUS;
typedef enum { HARMFUL, CAPSULE, EXPLOSION } EntityType;
typedef enum {
    CAPSULE_SLOW,
    CAPSULE_CATCH,
    CAPSULE_EXPAND,
    CAPSULE_DIVIDE,
    CAPSULE_LASER,
    CAPSULE_BREAK,
    CAPSULE_ADDITION,
    HARMFUL_1,
    HARMFUL_2,
    HARMFUL_3
} SpecificType;

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
};

AnimatedEntity create_entity(SpecificType type, Point position);
AnimatedEntity create_harmful(SpecificType harmfulType);
AnimatedEntity create_capsule();
Ball create_ball(Point position);
VAUS create_VAUS(Point position);
void update_VAUS_size(VAUS *vaus, int size);
#endif // ARKANOID_ENTITY_H
