#include "delta_time.h"
#include "config.h"

float time_scale = 1.0;
DeltaTime delta_time;

void init_delta_time() {
    delta_time.previous_time = SDL_GetPerformanceCounter();
    delta_time.current_time = delta_time.previous_time;
    delta_time.frequency = SDL_GetPerformanceFrequency();
    delta_time.dt = 0.0;
    delta_time.dt_target = 0;
}

void update_delta_time() {
    delta_time.previous_time = delta_time.current_time;
    delta_time.current_time = SDL_GetPerformanceCounter();
    delta_time.dt =
        (double) (delta_time.current_time - delta_time.previous_time) /
        delta_time.frequency * time_scale;
    delta_time.dt_target = delta_time.dt * FPS_TARGET * time_scale;
}

double get_delta_time() { return delta_time.dt; }

double get_delta_time_target() { return delta_time.dt_target; }

double get_current_fps() { return 1.0 / delta_time.dt * time_scale; }

void set_time_scale(float scale) { time_scale = scale; }
