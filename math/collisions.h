#ifndef ARKANOID_COLLISIONS_H
#define ARKANOID_COLLISIONS_H
#include "math.h"
#include "stdbool.h"

bool rect_rect_collision(Rectangle rect1, Rectangle rect2);
bool rect_circle_collision(Rectangle rect, Circle circ);
bool circle_circle_collision(Circle circ1, Circle circ2);

#endif // ARKANOID_COLLISIONS_H
