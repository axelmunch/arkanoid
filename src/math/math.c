#include "math.h"

double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
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

double degrees_to_radians(double degrees) { return degrees * M_PI / 180; }

double radians_to_degrees(double radians) { return radians * 180 / M_PI; }

void rotate_by_angle(double distance, double angle, Vector *vector) {
    const double a = degrees_to_radians(angle);
    vector->x = distance * cos(a);
    vector->y = distance * sin(a);
}
