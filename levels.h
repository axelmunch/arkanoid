#ifndef ARKANOID_LEVELS_H
#define ARKANOID_LEVELS_H

#include "audio.h"
#include "config.h"
#include "delta_time.h"
#include "entities/entities_structures.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Brick Brick;
typedef struct Level Level;

typedef enum {
    EMPTY,
    WHITE,
    ORANGE,
    CYAN,
    LIME,
    DARK_BLUE,
    GREEN,
    RED,
    BLUE,
    PINK,
    YELLOW,
    DARK_RED,
    OCEAN_BLUE,
    METAL,
    GOLD
} BrickType;

typedef enum {
    THEME_1,
    THEME_2,
    THEME_3,
    THEME_4,
    THEME_5,
    THEME_6,
} LevelTheme;

struct Brick {
    BrickType type;
    int durability;
    int max_animation;
    int current_animation;
    int time_before_next_animation;
    SpecificType capsule_reward;
};

struct Level {
    LevelTheme theme;
    int offset;
    int height;
    Brick bricks[LEVEL_HEIGHT][LEVEL_WIDTH];
};

Brick create_brick(BrickType type, SpecificType capsule_reward);
void restart_level_1(SDL_Surface *win_surf);
void reset_level();
void load_next_level(SDL_Surface *win_surf);
bool load_next_level_file();
void load_level(const char *filename);
bool is_level_completed();
bool update_level();
bool is_end_game();
Level *get_level();

#endif // ARKANOID_LEVELS_H
