#ifndef ARKANOID_SCORE_H
#define ARKANOID_SCORE_H

#include "levels.h"

void init_score();

void reset_score();

void add_score(int score);

void update_score();

void break_brick(BrickType brick_type);

int get_score();

int get_high_score();

void load_high_score();

void save_high_score();

#endif // ARKANOID_SCORE_H
