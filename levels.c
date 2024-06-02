#include "levels.h"

Level level;
int current_level = 0;

Brick create_brick(BrickType type, SpecificType capsule_reward) {
    Brick brick;
    brick.type = type;
    brick.current_animation = 0;
    brick.capsule_reward = capsule_reward;
    brick.time_before_next_animation = 0;

    if (type == METAL) {
        brick.durability = 8;
        brick.max_animation = 6;

    } else if (type == GOLD) {
        brick.durability = -1;
        brick.max_animation = 6;
    } else {
        brick.durability = 1;
        brick.max_animation = 0;
    }

    return brick;
}

void restart_level_1() { current_level = 0; }

void reset_level() {
    level.theme = THEME_1;
    level.offset = 0;
    level.height = 0;
    for (int y = 0; y < LEVEL_HEIGHT; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            level.bricks[y][x] = create_brick(EMPTY, CAPSULE_EMPTY);
        }
    }
}

void load_next_level() {
    current_level++;
    if (current_level <= MAX_LEVELS) {
        char filename[20];
        sprintf(filename, "levels/%d.level", current_level);
        load_level(filename);
        load_music(current_level);
    }
}

void load_level(const char *filename) {
    reset_level();

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }

    char line[8];

    // Theme
    fgets(line, sizeof(line), file);
    level.theme = atoi(line);

    // Offset
    fgets(line, sizeof(line), file);
    level.offset = atoi(line);

    // Height
    fgets(line, sizeof(line), file);
    level.height = atoi(line);

    // Bricks
    int x = 0;
    int y = level.offset;
    for (int i = 0; i < level.height * LEVEL_WIDTH; i++) {
        fgets(line, sizeof(line), file);
        BrickType type = atoi(line);
        fgets(line, sizeof(line), file);
        SpecificType capsule = atoi(line);
        level.bricks[y][x] = create_brick(type, capsule);
        x++;
        if (x == LEVEL_WIDTH) {
            x = 0;
            y++;
        }
    }
}

bool is_level_completed() {
    for (int y = level.offset; y < level.height + level.offset; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            if (level.bricks[y][x].type != EMPTY &&
                level.bricks[y][x].type != GOLD) {
                return false;
            }
        }
    }
    return true;
}

bool update_level() {
    // Return true if level complete

    Level *level = get_level();
    for (int y = level->offset; y < level->height + level->offset; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            Brick brick = level->bricks[y][x];

            if (brick.type == METAL || brick.type == GOLD) {
                if (brick.current_animation > 0) {
                    brick.time_before_next_animation -= get_delta_time() * 1000;
                    if (brick.time_before_next_animation <= 0) {
                        brick.time_before_next_animation = ANIMATION_TIMER_MS;
                        brick.current_animation = fmod(
                            brick.current_animation + 1, brick.max_animation);
                    }
                }

                level->bricks[y][x] = brick;
            }
        }
    }
    if (is_level_completed()) {
        return true;
    }

    return false;
}

Level *get_level() { return &level; }
