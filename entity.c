#include "entity.h"

AnimatedEntity create_entity(SpecificType type, Point position) {
    AnimatedEntity entity;
    switch (type) {
    case CAPSULE_SLOW:
    case CAPSULE_CATCH:
    case CAPSULE_EXPAND:
    case CAPSULE_DIVIDE:
    case CAPSULE_LASER:
    case CAPSULE_BREAK:
    case CAPSULE_ADDITION: {
        entity = create_capsule();
        break;
    }
    case HARMFUL_1:
    case HARMFUL_2:
    case HARMFUL_3: {
        entity = create_harmful(type);
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
AnimatedEntity create_harmful(SpecificType harmfulType) {
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
AnimatedEntity create_capsule() {
    AnimatedEntity capsule;
    capsule.type = CAPSULE;
    capsule.max_animation = 8;
    capsule.hit_box.width = 32;
    capsule.hit_box.height = 16;
    return capsule;
}
Ball create_ball(Point position) {
    Ball ball;
    ball.hit_box.origin = position;
    ball.hit_box.radius = 8;
    ball.velocity = 2.0;
    ball.direction = 42;
    return ball;
}
VAUS create_VAUS(Point position) {
    VAUS vaus;
    update_VAUS_size(&vaus, 5);
    vaus.hit_box.origin = position;
    vaus.hit_box.origin.x -= vaus.hit_box.width / 2;
    vaus.hit_box.origin.y -= vaus.hit_box.height;
    return vaus;
}

void update_VAUS_size(VAUS *vaus, int size) {
    vaus->expand_size = size;
    if (vaus->expand_size > VAUS_MAX_SIZE) {
        vaus->expand_size = VAUS_MAX_SIZE;
    }
    if (vaus->expand_size < 1) {
        vaus->expand_size = 1;
    }
    Textures VAUS_texture = vaus->expand_size + VausSize1 - 1;
    int mock;
    int width;
    int height;
    get_texture_dimensions(VAUS_texture, &mock, &mock, &width, &height);
    vaus->hit_box.width = width;
    vaus->hit_box.height = height;
}
