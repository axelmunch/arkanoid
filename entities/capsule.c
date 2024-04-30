#include "capsule.h"

#include "entity.h"
void apply_expand_capsule(VAUS *vaus) {
    update_VAUS_size(vaus, vaus->expand_size + 1);
}

void apply_slow_capsule(Ball *ball) {
    if (ball->velocity / 2 > 2) {
        ball->velocity /= 2;
    };
}
