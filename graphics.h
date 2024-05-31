#ifndef ARKANOID_GRAPHICS_H
#define ARKANOID_GRAPHICS_H

#include "vaus.h"
#include "entities/ball.h"
#include "entities/entities_spawner.h"
#include "text.h"
#include "config.h"
#include "levels.h"
#include <SDL.h>

void draw_background(SDL_Surface *win_surf);
void draw_borders_1(SDL_Surface *win_surf);
void draw_borders_2(SDL_Surface *win_surf);
void draw_level(SDL_Surface *win_surf);
void draw_entities(SDL_Surface *win_surf);
void draw_score(SDL_Surface *win_surf);
void draw(SDL_Surface *win_surf, bool multiplayer_mode, bool dead);

#endif //ARKANOID_GRAPHICS_H
