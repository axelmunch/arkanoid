#ifndef ARKANOID_MATH_H
#define ARKANOID_MATH_H
#include <math.h>

typedef struct Point Point;
typedef struct Circle Circle;
typedef struct Rectangle Rectangle;

struct Point {
    double x;
    double y;
};

struct Circle {
    Point origin;
    double radius;
};

struct Rectangle {
    Point origin;
    double width;
    double height;
};

double distance(Point p1, Point p2);
double clamp(double value, double min, double max);

#endif // ARKANOID_MATH_H
