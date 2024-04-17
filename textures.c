#include "textures.h"
#include <math.h>
#include <stdbool.h>

#include <stdlib.h>

char *texture_file = "Arkanoid_sprites.bmp";

SDL_Surface *texture_bitmap = NULL;

void init_texture() {
    texture_bitmap = SDL_LoadBMP(texture_file);
    SDL_SetColorKey(texture_bitmap, true, 0);
}

void get_texture_dimensions(Textures texture, int *pos_x, int *pos_y,
                            int *width, int *height) {
    switch (texture) {
    case BackgroundTheme1:
        *pos_x = 0;
        *pos_y = 128;
        *width = 48;
        *height = 64;
        break;
    case BackgroundTheme2:
        *pos_x = 64;
        *pos_y = 128;
        *width = 64;
        *height = 64;
        break;
    case BackgroundTheme3:
        *pos_x = 128;
        *pos_y = 128;
        *width = 64;
        *height = 64;
        break;
    case BackgroundTheme4:
        *pos_x = 192;
        *pos_y = 128;
        *width = 64;
        *height = 64;
        break;
    case BackgroundTheme5:
        *pos_x = 256;
        *pos_y = 128;
        *width = 64;
        *height = 64;
        break;
    case BackgroundTheme6:
        *pos_x = 320;
        *pos_y = 128;
        *width = 64;
        *height = 64;
        break;
    case BallTexture:
        *pos_x = 80;
        *pos_y = 64;
        *width = 16;
        *height = 16;
        break;
    case VausSize1:
        *pos_x = 384;
        *pos_y = 128 + 16 * 0;
        *width = 64 + 10 * 0;
        *height = 16;
        break;
    case VausSize2:
        *pos_x = 384;
        *pos_y = 128 + 16 * 1;
        *width = 74;
        *height = 16;
        break;
    case VausSize3:
        *pos_x = 384;
        *pos_y = 128 + 16 * 2;
        *width = 82;
        *height = 16;
        break;
    case VausSize4:
        *pos_x = 384;
        *pos_y = 128 + 16 * 3;
        *width = 90;
        *height = 16;
        break;
    case VausSize5:
        *pos_x = 384;
        *pos_y = 128 + 16 * 4;
        *width = 98;
        *height = 16;
        break;
    case VausSize6:
        *pos_x = 384;
        *pos_y = 128 + 16 * 5;
        *width = 108;
        *height = 16;
        break;
    case VausSize7:
        *pos_x = 384;
        *pos_y = 128 + 16 * 6;
        *width = 118;
        *height = 16;
        break;
    case VausSize8:
        *pos_x = 384;
        *pos_y = 128 + 16 * 7;
        *width = 128;
        *height = 16;
        break;
    }
    if (texture >= BrickWhite && texture <= BrickGold6) {
        *pos_x = ((texture - BrickWhite) % 6) * 32;
        *pos_y = ((texture - BrickWhite) / 6) * 16;

        *width = 32;
        *height = 16;
    }
}

void draw_texture(SDL_Surface *surface, Textures texture, int x, int y,
                  bool centered) {
    int pos_x, pos_y, width, height;
    get_texture_dimensions(texture, &pos_x, &pos_y, &width, &height);

    SDL_Rect src = {pos_x, pos_y, width, height};
    SDL_Rect dst = {x, y, 0, 0};
    if (centered) {
        dst.x -= width / 2;
        dst.y -= height / 2;
    }

    SDL_BlitSurface(texture_bitmap, &src, surface, &dst);
}

void draw_brick(SDL_Surface *surface, BrickType type, int brick_animation,
                int x, int y) {
    Textures brickTexture = type - 1 + BrickWhite;

    if (type == METAL) {
        brickTexture = BrickMetal1 + brick_animation;
    }
    if (type == GOLD) {
        brickTexture = BrickGold1 + brick_animation;
    }

    draw_texture(surface, brickTexture, x, y, false);
}

void draw_vaus(SDL_Surface *surface, VAUS vaus) {
    Textures normalizedVausTexture = vaus.expand_size + VausSize1 - 1;
    draw_texture(surface, normalizedVausTexture, (int) vaus.hit_box.origin.x,
                 (int) vaus.hit_box.origin.y, false);
}