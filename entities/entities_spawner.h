#ifndef ARKANOID_ENTITIES_SPAWNER_H
#define ARKANOID_ENTITIES_SPAWNER_H

#include "../config.h"
#include "../delta_time.h"
#include "../math/math.h"
#include "../score.h"
#include "../textures.h"
#include "../vaus.h"
#include "entities_structures.h"
#include "entity.h"
#include <stdlib.h>

typedef struct SpawnedEntities SpawnedEntities;

struct SpawnedEntities {
    AnimatedEntity entities[MAX_ENTITIES];
    int current_entities_count;
};

void init_spawner();
void reset_spawner();
void add_entity(AnimatedEntity entity);
void update_spawner();
void remove_entity(int index);
void explode_entity(int index);
bool laser_collides_with_brick(const AnimatedEntity *entity,
                               SDL_Surface *win_surf);
bool handle_laser_entities_collision(AnimatedEntity *laser_entity,
                                     int laser_index);
bool update_entities(SDL_Surface *win_surf, bool multiplayer_mode);
SpawnedEntities *get_entities();

#endif // ARKANOID_ENTITIES_SPAWNER_H
