#ifndef ARKANOID_ENTITY_H
#define ARKANOID_ENTITY_H

#include "../config.h"
#include "../math/math.h"
#include "../textures.h"
#include "entities_structures.h"



AnimatedEntity create_entity(SpecificType type, Point position);
AnimatedEntity create_harmful(SpecificType harmfulType);
AnimatedEntity create_capsule();
Ball create_ball(Point position);
VAUS create_VAUS(Point position);
void update_VAUS_size(VAUS *vaus, int size);
#endif // ARKANOID_ENTITY_H
