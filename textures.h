#ifndef ARKANOID_TEXTURES_H
#define ARKANOID_TEXTURES_H

#include "entities/entities_structures.h"
#include "levels.h"
#include "math/math.h"
#include <SDL.h>
#include <stdbool.h>

typedef enum {
    BackgroundTheme1,
    BackgroundTheme2,
    BackgroundTheme3,
    BackgroundTheme4,
    BackgroundTheme5,
    BackgroundTheme6,
    BallTexture,
    VausSize1,
    VausSize2,
    VausSize3,
    VausSize4,
    VausSize5,
    VausSize6,
    VausSize7,
    VausSize8,
    BrickWhite,
    BrickOrange,
    BrickCyan,
    BrickLime,
    BrickDarkBlue,
    BrickGreen,
    BrickRed,
    BrickBlue,
    BrickPink,
    BrickYellow,
    BrickDarkRed,
    BrickOceanBlue,
    BrickMetal1,
    BrickMetal2,
    BrickMetal3,
    BrickMetal4,
    BrickMetal5,
    BrickMetal6,
    BrickGold1,
    BrickGold2,
    BrickGold3,
    BrickGold4,
    BrickGold5,
    BrickGold6,
    EntityHarmful1_1,
    EntityHarmful1_2,
    EntityHarmful1_3,
    EntityHarmful1_4,
    EntityHarmful1_5,
    EntityHarmful1_6,
    EntityHarmful1_7,
    EntityHarmful1_8,
    EntityHarmful2_1,
    EntityHarmful2_2,
    EntityHarmful2_3,
    EntityHarmful2_4,
    EntityHarmful2_5,
    EntityHarmful2_6,
    EntityHarmful2_7,
    EntityHarmful2_8,
    EntityHarmful2_9,
    EntityHarmful2_10,
    EntityHarmful2_11,
    EntityHarmful3_1,
    EntityHarmful3_2,
    EntityHarmful3_3,
    EntityHarmful3_4,
    EntityHarmful3_5,
    EntityHarmful3_6,
    EntityHarmful3_7,
    EntityHarmful3_8,
    EntityHarmful3_9,
    EntityHarmful3_10,
    EntityHarmful3_11,
    EntityHarmful3_12,
    EntityHarmful3_13,
    EntityHarmful3_14,
    EntityHarmful3_15,
    EntityHarmful3_16,
    EntityHarmful3_17,
    EntityHarmful3_18,
    EntityHarmful3_19,
    EntityHarmful3_20,
    EntityHarmful3_21,
    EntityHarmful3_22,
    EntityHarmful3_23,
    EntityHarmful3_24,
    Explosion_1,
    Explosion_2,
    Explosion_3,
    Explosion_4,
    Explosion_5,
    Explosion_6
} Textures;

void init_texture();

void get_texture_dimensions(Textures texture, int *pos_x, int *pos_y,
                            int *width, int *height);

void draw_texture(SDL_Surface *surface, Textures texture, int x, int y,
                  bool centered);

void draw_brick(SDL_Surface *surface, BrickType type, int brick_animation,
                int x, int y);

void draw_vaus(SDL_Surface *surface, VAUS vaus);

void draw_entity(SDL_Surface *surface, AnimatedEntity entity);

#endif // ARKANOID_TEXTURES_H
