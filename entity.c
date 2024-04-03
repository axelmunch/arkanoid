#include "entity.h"

AnimatedEntity createEntity(SpecificType type, Point position) {
    AnimatedEntity entity;
    switch (type) {
    case CAPSULE_SLOW:
    case CAPSULE_CATCH:
    case CAPSULE_EXPAND:
    case CAPSULE_DIVIDE:
    case CAPSULE_LASER:
    case CAPSULE_BREAK:
    case CAPSULE_ADDITION: {
        entity = createCapsule();
        break;
    }
    case HARMFUL_1:
    case HARMFUL_2:
    case HARMFUL_3: {
        entity = createHarmful(type);
        break;
    }
    }
    entity.time_before_next_animation = ANIMATION_TIMER_MS;
    entity.velocity = 1.5;
    entity.direction = 270; // corresponds to -90 deg
    entity.current_animation = 1;
    entity.specific_type = type;
    entity.hit_box.origin = position;
    return entity;
}
AnimatedEntity createHarmful(SpecificType harmfulType) {
    AnimatedEntity harmful;
    harmful.type = HARMFUL;
    switch (harmfulType) {
    case HARMFUL_1:
        harmful.max_animation = 8;
        break;
    case HARMFUL_2:
        harmful.max_animation = 11;
        break;
    default:
        harmful.max_animation = 24;
        break;
    }
    harmful.hit_box.width = 32;
    harmful.hit_box.height = 32;
    return harmful;
}
AnimatedEntity createCapsule() {
    AnimatedEntity capsule;
    capsule.type = CAPSULE;
    capsule.max_animation = 8;
    capsule.hit_box.width = 32;
    capsule.hit_box.height = 16;
    return capsule;
}
Ball createBall(Point position) {
    Ball ball;
    ball.hit_box.origin = position;
    ball.hit_box.radius = 8;
    ball.velocity = 2.0;
    ball.direction = 42;
    return ball;
}
VAUS createVAUS(Point position) {
    VAUS vaus;
    vaus.hit_box.width = 64;
    vaus.hit_box.height = 16;
    vaus.hit_box.origin = position;
    vaus.hit_box.origin.x -= vaus.hit_box.width / 2;
    vaus.hit_box.origin.y -= vaus.hit_box.height;
    vaus.expand_size = 5;
    return vaus;
}
