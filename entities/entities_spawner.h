#ifndef ARKANOID_ENTITIES_SPAWNER_H
#define ARKANOID_ENTITIES_SPAWNER_H

#include "../config.h"
#include "../delta_time.h"
#include "../math/math.h"
#include "entities_structures.h"
#include "entity.h"

typedef struct SpawnedEntities SpawnedEntities;

struct SpawnedEntities {
    AnimatedEntity entities[MAX_ENTITIES];
    int current_entitiesCount;
};

void init_spawner();
void reset_spawner();
void update_spawner();
void remove_entity(int index);
void explode_entity(int index);
SpawnedEntities *get_entities();

#endif // ARKANOID_ENTITIES_SPAWNER_H