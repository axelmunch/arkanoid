#ifndef ARKANOID_VAUS_H
#define ARKANOID_VAUS_H

#include "config.h"
#include "delta_time.h"
#include "entities/ball.h"
#include "entities/capsule.h"
#include "entities/entities_structures.h"
#include "entities/entity.h"
#include "math/collisions.h"
#include <SDL.h>

void init_vaus(SDL_Surface *win_surf);
void reset_vaus();
void move_VAUS(double distance, int vaus_index, bool multiplayer_mode);
VAUS *get_vaus();

#endif // ARKANOID_VAUS_H
