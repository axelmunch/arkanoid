#ifndef ARKANOID_TEXTURES_H
#define ARKANOID_TEXTURES_H

#include "config.h"
#include "delta_time.h"
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
    VausBlinkingLeft,
    VausBlinkingRight,
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
    EntityLaser_1,
    EntityLaser_2,
    Explosion_1,
    Explosion_2,
    Explosion_3,
    Explosion_4,
    Explosion_5,
    Explosion_6,
    EntityMiniVaus,
    CapsuleSlow_1,
    CapsuleSlow_2,
    CapsuleSlow_3,
    CapsuleSlow_4,
    CapsuleSlow_5,
    CapsuleSlow_6,
    CapsuleSlow_7,
    CapsuleSlow_8,
    CapsuleCatch_1,
    CapsuleCatch_2,
    CapsuleCatch_3,
    CapsuleCatch_4,
    CapsuleCatch_5,
    CapsuleCatch_6,
    CapsuleCatch_7,
    CapsuleCatch_8,
    CapsuleLaser_1,
    CapsuleLaser_2,
    CapsuleLaser_3,
    CapsuleLaser_4,
    CapsuleLaser_5,
    CapsuleLaser_6,
    CapsuleLaser_7,
    CapsuleLaser_8,
    CapsuleExpand_1,
    CapsuleExpand_2,
    CapsuleExpand_3,
    CapsuleExpand_4,
    CapsuleExpand_5,
    CapsuleExpand_6,
    CapsuleExpand_7,
    CapsuleExpand_8,
    CapsuleDivide_1,
    CapsuleDivide_2,
    CapsuleDivide_3,
    CapsuleDivide_4,
    CapsuleDivide_5,
    CapsuleDivide_6,
    CapsuleDivide_7,
    CapsuleDivide_8,
    CapsuleBreak_1,
    CapsuleBreak_2,
    CapsuleBreak_3,
    CapsuleBreak_4,
    CapsuleBreak_5,
    CapsuleBreak_6,
    CapsuleBreak_7,
    CapsuleBreak_8,
    CapsuleAddition_1,
    CapsuleAddition_2,
    CapsuleAddition_3,
    CapsuleAddition_4,
    CapsuleAddition_5,
    CapsuleAddition_6,
    CapsuleAddition_7,
    CapsuleAddition_8,
    BorderSide,
    BorderCornerLeft,
    BorderCornerRight,
    BorderTop,
    BorderTopBigger,
    BlackBackground
} Textures;

void init_texture();

void get_texture_dimensions(Textures texture, int *pos_x, int *pos_y,
                            int *width, int *height);

void draw_texture(SDL_Surface *surface, Textures texture, int x, int y,
                  bool centered);

void draw_brick(SDL_Surface *surface, BrickType type, int brick_animation,
                int x, int y);

void draw_vaus(SDL_Surface *surface, VAUS vaus, int vaus_index);

void draw_entity(SDL_Surface *surface, AnimatedEntity entity);

#endif // ARKANOID_TEXTURES_H