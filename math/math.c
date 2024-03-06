#include "math.h"

double distance(Point p1, Point p2) {
    return sqrt((p2.x - p1.x) + (p2.y - p2.y));
}

double clamp(double value, double min, double max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}
