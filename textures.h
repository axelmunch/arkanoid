#ifndef ARKANOID_TEXTURES_H
#define ARKANOID_TEXTURES_H

#include <SDL.h>
#include <stdbool.h>

typedef enum {
    BackgroundTile,
    BallTexture,
    VausSize1,
    VausSize2,
    VausSize3,
    VausSize4,
    VausSize5,
    VausSize6,
    VausSize7,
    VausSize8,
} Textures;

void init_texture();
void get_texture_dimensions(Textures texture, int *pos_x, int *pos_y,
                            int *width, int *height);
void draw_texture(SDL_Surface *surface, Textures texture, int x, int y,
                  bool centered);

#endif // ARKANOID_TEXTURES_H
