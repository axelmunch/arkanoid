#ifndef BALL_H
#define BALL_H

#include "../config.h"
#include "../levels.h"
#include "../score.h"
#include "../vaus.h"
#include "capsule.h"
#include "entities_spawner.h"
#include "entities_structures.h"
#include <SDL.h>

typedef struct Balls Balls;
struct Balls {
    Ball spawned_balls[MAX_ENTITIES];
    int current_balls_count;
};

void add_ball(Ball ball);
void remove_ball(int index);
void reset_balls();
bool ball_collides_with_horizontal_border(const Ball *ball);
bool ball_collides_with_vertical_border(SDL_Surface *win_surf,
                                        const Ball *ball);
bool ball_collides_with_brick(SDL_Surface *win_surf, const Ball *ball);
bool ball_collides_with_entity(Ball *ball);
bool apply_ball_effect(double ball_direction, bool add_effect);
bool update_balls(SDL_Surface *win_surf, bool multiplayer_mode);
Balls *get_balls();

#endif // BALL_H
