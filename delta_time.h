#ifndef ARKANOID_DELTA_TIME_H
#define ARKANOID_DELTA_TIME_H

#include <SDL.h>

struct delta_time_struct {
    Uint64 previous_time;
    Uint64 current_time;
    Uint64 frequency; // Performance frequency
    double dt;
    double dt_target;
};

typedef struct delta_time_struct DeltaTime;

void init_delta_time();

void update_delta_time();

double get_delta_time();

double get_delta_time_target();

double get_current_fps();

#endif // ARKANOID_DELTA_TIME_H
