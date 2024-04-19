#include "entities_spawner.h"

SpawnedEntities spawnedEntities;
int x_spawn_position = 150;
int y_spawn_position = 50;
float time_between_spawn = 3;
float time_since_last_spawn = 0.0;

void init_spawner() { reset_spawner(); }

void reset_spawner() {
    spawnedEntities.current_entitiesCount = 0;
    float time_since_last_spawn = 0.0;
}

void update_spawner() {
    time_since_last_spawn += get_delta_time();

    // Spawn
    if (time_since_last_spawn >= time_between_spawn) {
        time_since_last_spawn = 0.0;
        if (spawnedEntities.current_entitiesCount < MAX_ENTITIES) {
            Point spawn_position = {x_spawn_position, y_spawn_position};
            spawnedEntities.entities[spawnedEntities.current_entitiesCount] =
                create_entity(HARMFUL_3, spawn_position);
            spawnedEntities.current_entitiesCount++;
        }
    }
}

void remove_entity(int index) {
    spawnedEntities.current_entitiesCount--;
    for (int i = index; i < spawnedEntities.current_entitiesCount; i++) {
        spawnedEntities.entities[i] = spawnedEntities.entities[i + 1];
    }
}

void explode_entity(int index) {
    Point position = spawnedEntities.entities[index].hit_box.origin;

    remove_entity(index);

    spawnedEntities.entities[spawnedEntities.current_entitiesCount] =
        create_entity(EXPLOSION_TYPE, position);
    spawnedEntities.current_entitiesCount++;
}

SpawnedEntities *get_entities() { return &spawnedEntities; }
