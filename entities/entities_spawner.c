#include "entities_spawner.h"

SpawnedEntities spawned_entities;
int x_spawn_position = 200;
int y_spawn_position = 50;
float time_between_spawn = 3;
float time_since_last_spawn = 0.0;

void init_spawner() { reset_spawner(); }

void reset_spawner() {
    spawned_entities.current_entities_count = 0;
    time_since_last_spawn = 0.0;
}

void update_spawner() {
    time_since_last_spawn += get_delta_time();

    // Spawn
    if (time_since_last_spawn >= time_between_spawn) {
        time_since_last_spawn = 0.0;
        if (spawned_entities.current_entities_count < MAX_ENTITIES) {
            Point spawn_position = {x_spawn_position * (rand() % 2 + 1) - 16,
                                    y_spawn_position};
            SpecificType entity_to_spawn = HARMFUL_1 + rand() % 3;
            spawned_entities.entities[spawned_entities.current_entities_count] =
                create_entity(entity_to_spawn, spawn_position);
            spawned_entities.current_entities_count++;
        }
    }
}

void remove_entity(int index) {
    spawned_entities.current_entities_count--;
    for (int i = index; i < spawned_entities.current_entities_count; i++) {
        spawned_entities.entities[i] = spawned_entities.entities[i + 1];
    }
}

void explode_entity(int index) {
    Point position = spawned_entities.entities[index].hit_box.origin;

    remove_entity(index);

    spawned_entities.entities[spawned_entities.current_entities_count] =
        create_entity(EXPLOSION_TYPE, position);
    spawned_entities.current_entities_count++;
}

SpawnedEntities *get_entities() { return &spawned_entities; }
