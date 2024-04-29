#include "collisions.h"

bool rect_rect_collision(Rectangle rect1, Rectangle rect2) {
    return (rect1.origin.x <= rect2.origin.x + rect2.width &&
            rect1.origin.x + rect1.width >= rect2.origin.x &&
            rect1.origin.y <= rect2.origin.y + rect2.height &&
            rect1.origin.y + rect1.height >= rect2.origin.y);
}

bool rect_circle_collision(Rectangle rect, Circle circ) {
    Point closestP = {
        clamp(circ.origin.x, rect.origin.x, rect.origin.x + rect.width),
        clamp(circ.origin.y, rect.origin.y, rect.origin.y + rect.height)};
    return distance(closestP, circ.origin) <= circ.radius;
}

bool circle_circle_collision(Circle circ1, Circle circ2) {
    double d = distance(circ1.origin, circ2.origin);
    return d <= circ1.radius + circ2.radius;
}
