#ifndef ARKANOID_TEXTURES_H
#define ARKANOID_TEXTURES_H

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
} Textures;

void init_texture();

void get_texture_dimensions(Textures texture, int *pos_x, int *pos_y,
                            int *width, int *height);

void draw_texture(SDL_Surface *surface, Textures texture, int x, int y,
                  bool centered);

void draw_brick(SDL_Surface *surface, BrickType type, int brick_animation,
                int x, int y);

void draw_vaus(SDL_Surface *surface, VAUS vaus);

#endif // ARKANOID_TEXTURES_H
