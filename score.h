#ifndef ARKANOID_SCORE_H
#define ARKANOID_SCORE_H

#include "levels.h"

void reset_score();

void add_score(int score);

void break_brick(BrickType brick_type);

int get_score();

#endif // ARKANOID_SCORE_H
