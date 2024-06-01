#include "vaus.h"

VAUS vaus[2];

SDL_Surface *win_surf_vaus = NULL;

void init_vaus(SDL_Surface *win_surf) {
    win_surf_vaus = win_surf;
    reset_vaus();
}

void reset_vaus() {
    Point vausPosition = {win_surf_vaus->w / 2, win_surf_vaus->h - 32};
    vaus[0] = create_VAUS(vausPosition);
    vaus[1] = create_VAUS(vausPosition);
}

void move_VAUS(double distance, int vaus_index) {
    vaus[vaus_index].hit_box.origin.x += distance * get_delta_time_target();
    if (vaus[vaus_index].hit_box.origin.x < GAME_BORDER_X) {
        vaus[vaus_index].hit_box.origin.x = GAME_BORDER_X;
    } else if (vaus[vaus_index].hit_box.origin.x +
                   vaus[vaus_index].hit_box.width >
               win_surf_vaus->w - GAME_BORDER_X) {
        vaus[vaus_index].hit_box.origin.x =
            win_surf_vaus->w - GAME_BORDER_X - vaus[vaus_index].hit_box.width;
    }

    Balls *balls = get_balls();
    for (int i = 0; i < balls->current_balls_count; i++) {
        Ball *ball = &balls->spawned_balls[i];
        if (rect_circle_collision(vaus[vaus_index].hit_box, ball->hit_box)) {
            ball->hit_box.origin.x += distance * get_delta_time_target();
            if (get_active_capsule() == CAPSULE_CATCH) {
                catch_ball(ball, vaus[vaus_index].hit_box, vaus_index);
            }
            if ((ball->hit_box.origin.x <
                 ball->hit_box.radius + GAME_BORDER_X) ||
                (ball->hit_box.origin.x >
                 (win_surf_vaus->w - GAME_BORDER_X - ball->hit_box.radius))) {
                ball->hit_box.origin.x -= distance * get_delta_time_target();
                ball->hit_box.origin.y =
                    vaus[vaus_index].hit_box.origin.y - ball->hit_box.radius;
            }
        }

        // If double collision, get ball above vaus
        if (rect_circle_collision(vaus[1 - vaus_index].hit_box,
                                  ball->hit_box)) {
            ball->hit_box.origin.y =
                vaus[vaus_index].hit_box.origin.y - ball->hit_box.radius;
        }
    }
    update_attached_ball(vaus[0].hit_box, 0);
    update_attached_ball(vaus[1].hit_box, 1);
}

VAUS *get_vaus() { return vaus; }