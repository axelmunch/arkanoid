#include "capsule.h"

#include "entity.h"
void apply_expand_capsule(VAUS *vaus) {
    update_VAUS_size(vaus, vaus->expand_size + 1);
}
