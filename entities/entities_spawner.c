#include "entities_spawner.h"

SpawnedEntities spawned_entities;
int x_spawn_position = 200;
int y_spawn_position = 50;
float time_between_spawn = 3;
float time_since_last_spawn = 0.0;
int entity_offset;

void init_spawner() { reset_spawner(); }

void reset_spawner() {
    int mock;
    get_texture_dimensions(HARMFUL_1, &mock, &mock, &entity_offset, &mock);
    spawned_entities.current_entities_count = 0;
    time_since_last_spawn = 0.0;
}

void add_entity(const AnimatedEntity entity) {
    spawned_entities.entities[spawned_entities.current_entities_count] = entity;
    spawned_entities.current_entities_count++;
}

void update_spawner() {
    time_since_last_spawn += get_delta_time();

    // Spawn
    if (time_since_last_spawn >= time_between_spawn) {
        time_since_last_spawn = 0.0;
        if (spawned_entities.current_entities_count < MAX_ENTITIES) {
            const Point spawn_position = {x_spawn_position * (rand() % 2 + 1) -
                                              entity_offset / 2,
                                          y_spawn_position};
            SpecificType entity_to_spawn = HARMFUL_1 + rand() % 3;
            add_entity(create_entity(entity_to_spawn, spawn_position));
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

bool laser_collides_with_brick(const AnimatedEntity *entity, SDL_Surface *win_surf) {
    Level *level = get_level();
    const int offset_x = (win_surf->w - LEVEL_WIDTH * 32) / 2;
    for (int y = level->offset; y < level->height + level->offset; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            Brick brick = level->bricks[y][x];
            if (brick.type != EMPTY) {
                Rectangle brick_hitbox;
                brick_hitbox.origin.x = offset_x + x * BRICK_WIDTH;
                brick_hitbox.origin.y = LEVEL_OFFSET_Y + y * BRICK_HEIGHT;
                brick_hitbox.height = BRICK_HEIGHT;
                brick_hitbox.width = BRICK_WIDTH;
                if (rect_rect_collision(brick_hitbox, entity->hit_box)) {
                    // Animation
                    if (brick.type == METAL || brick.type == GOLD) {
                        brick.current_animation = 1;
                        brick.time_before_next_animation = ANIMATION_TIMER_MS;
                        level->bricks[y][x] = brick;
                    }

                    if (brick.type != GOLD) {
                        brick.durability = 0;
                        if (brick.capsule_reward != CAPSULE_EMPTY) {
                            add_entity(create_entity(brick.capsule_reward,
                                                     brick_hitbox.origin));
                        }
                        score_break_brick(brick.type);
                        level->bricks[y][x] =
                            create_brick(EMPTY, CAPSULE_EMPTY);
                    }

                    return true;
                }
            }
        }
    }
    return false;
}

bool update_entities(SDL_Surface *win_surf) {
    // Return true if should change level (capsule break)

    SpawnedEntities *entities = get_entities();
    for (int i = 0; i < entities->current_entities_count; i++) {
        AnimatedEntity *entity = &entities->entities[i];

        entity->time_before_next_animation -= get_delta_time() * 1000;
        if (entity->time_before_next_animation <= 0) {
            entity->time_before_next_animation = ANIMATION_TIMER_MS;
            entity->current_animation =
                fmod(entity->current_animation + 1, entity->max_animation);
        }

        if (entity->type == EXPLOSION ||
            entity->specific_type == LASER_EXPLOSION) {
            if (entity->current_animation == entity->max_animation - 1) {
                remove_entity(i);
            }
            continue;
        }

        // Change direction
        if (entity->type == HARMFUL) {
            entity->time_before_direction_change -= get_delta_time() * 1000;
            if (entity->time_before_direction_change <= 0) {
                entity->time_before_direction_change =
                    DIRECTION_CHANGE_TIMER_MS;
                entity->direction =
                    fmod(entity->direction + (rand() % 90) - 45, 360);
            }
        }

        // Move
        Vector entity_movement;
        rotate_by_angle(entity->velocity * get_delta_time_target(),
                        entity->direction, &entity_movement);
        if (entity->type == HARMFUL) {
            entity_movement.y -= get_delta_time() * 5;
        }
        if ((entity->hit_box.origin.x + entity_movement.x > GAME_BORDER_X &&
             entity->hit_box.origin.x + entity_movement.x +
                     entity->hit_box.width <
                 win_surf->w - GAME_BORDER_X) ||
            entity->type == CAPSULE) {
            entity->hit_box.origin.x += entity_movement.x;
        } else {
            entity->direction = fmod(entity->direction + 180, 360);
        }
        if (entity->hit_box.origin.y - entity_movement.y > GAME_BORDER_TOP ||
            entity->type == CAPSULE) {
            entity->hit_box.origin.y -= entity_movement.y;
        } else {
            if (entity->type == LASER) {
                remove_entity(i);
                continue;
            }
            entity->direction = fmod(entity->direction + 180, 360);
        }

        if (entity->hit_box.origin.y > win_surf->h) {
            remove_entity(i);
            continue;
        }

        // Collision
        VAUS *vaus = get_vaus();
        if (entity->type == HARMFUL &&
            (rect_rect_collision(entity->hit_box, vaus[0].hit_box)||rect_rect_collision(entity->hit_box, vaus[1].hit_box))) {
            explode_entity(i);
            add_score(150);
        }
        if (entity->type == LASER) {
            if (laser_collides_with_brick(entity, win_surf)) {
                add_entity(
                    create_entity(LASER_EXPLOSION, entity->hit_box.origin));
                remove_entity(i);
            }
        }

        // Capsules
        if (entity->type == CAPSULE && (rect_rect_collision(entity->hit_box, vaus[0].hit_box) || rect_rect_collision(entity->hit_box, vaus[1].hit_box))) {
            switch (entity->specific_type) {
            case CAPSULE_EXPAND:
                if(rect_rect_collision(entity->hit_box, vaus[0].hit_box))
                {
                    apply_expand_capsule(win_surf, &vaus[0], 0);
                }
                else {
                    apply_expand_capsule(win_surf, &vaus[1], 1);
                }
                break;
            case CAPSULE_SLOW:
                apply_slow_capsule();
                break;
            case CAPSULE_BREAK:
                return true;
                break;
            case CAPSULE_DIVIDE:
                apply_divide_capsule();
                break;
            case CAPSULE_CATCH:
                apply_catch_capsule();
                break;
            case CAPSULE_LASER:
                apply_laser_capsule();
                break;
            case CAPSULE_ADDITION:
                apply_addition_capsule();
                break;
            default:
                break;
            }
            remove_entity(i);
        }
    }

    return false;
}

SpawnedEntities *get_entities() { return &spawned_entities; }
