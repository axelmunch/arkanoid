#ifndef ARKANOID_GRAPHICS_H
#define ARKANOID_GRAPHICS_H

#include "config.h"
#include "entities/ball.h"
#include "entities/entities_spawner.h"
#include "levels.h"
#include "text.h"
#include "vaus.h"
#include <SDL.h>

void draw_background(SDL_Surface *win_surf);
void draw_borders_1(SDL_Surface *win_surf);
void draw_borders_2(SDL_Surface *win_surf);
void draw_level(SDL_Surface *win_surf);
void draw_entities(SDL_Surface *win_surf);
void draw_score(SDL_Surface *win_surf);
void draw_end_game(SDL_Surface *win_surf);
void draw_lives(SDL_Surface *win_surf, int lives);
void draw(SDL_Surface *win_surf, bool multiplayer_mode, int lives);

#endif // ARKANOID_GRAPHICS_H
