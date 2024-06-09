#include "graphics.h"

int dead_text_width = 0;
int high_score_text_width = 0;
int high_score_value_text_width = 0;

void draw_background(SDL_Surface *win_surf) {
    Level *level = get_level();
    LevelTheme level_theme = level->theme;
    Textures theme_texture = BackgroundTheme1 + level_theme;
    int mock, level_theme_width, level_theme_height;
    get_texture_dimensions(theme_texture, &mock, &mock, &level_theme_width,
                           &level_theme_height);
    for (int j = GAME_BORDER_TOP; j < win_surf->h; j += level_theme_height) {
        for (int i = GAME_BORDER_X; i < win_surf->w - GAME_BORDER_X;
             i += level_theme_width) {
            draw_texture(win_surf, theme_texture, i, j, false);
        }
    }

    // Black background
    int black_background_width, black_background_height;
    get_texture_dimensions(BlackBackground, &mock, &mock,
                           &black_background_width, &black_background_height);
    for (int i = GAME_BORDER_X - black_background_width;
         i > -black_background_width; i -= 32) {
        for (int j = 0; j < win_surf->h; j += black_background_height) {
            draw_texture(win_surf, BlackBackground, i, j, false);
        }
    }
    for (int i = win_surf->w - GAME_BORDER_X; i < win_surf->w;
         i += black_background_width) {
        for (int j = 0; j < win_surf->h; j += black_background_height) {
            draw_texture(win_surf, BlackBackground, i, j, false);
        }
    }
    for (int i = GAME_BORDER_X; i < win_surf->w - GAME_BORDER_X;
         i += black_background_width) {
        for (int j = GAME_BORDER_TOP - black_background_height;
             j > -black_background_height; j -= black_background_height) {
            draw_texture(win_surf, BlackBackground, i, j, false);
        }
    }
}

void draw_end_game(SDL_Surface *win_surf) {
    SDL_FillRect(win_surf, NULL, SDL_MapRGB(win_surf->format, 0, 0, 0));

    dead_text_width =
        draw_text(win_surf, "VICTORY ! Press SPACE to restart",
                  win_surf->w / 2 - dead_text_width / 2, win_surf->h / 2);
    draw_score(win_surf);
}

void draw_borders_1(SDL_Surface *win_surf) {
    // Top
    int mock, border_top_width, border_top_height;
    get_texture_dimensions(BorderTop, &mock, &mock, &border_top_width,
                           &border_top_height);
    for (int i = GAME_BORDER_X;
         i < win_surf->w - GAME_BORDER_X - border_top_width;
         i += border_top_width) {
        draw_texture(win_surf, BorderTop, i,
                     GAME_BORDER_TOP - border_top_height, false);
    }
    draw_texture(win_surf, BorderTop,
                 win_surf->w - GAME_BORDER_X - border_top_width,
                 GAME_BORDER_TOP - border_top_height, false);

    // Top bigger
    int border_top_bigger_width, border_top_bigger_height;
    get_texture_dimensions(BorderTopBigger, &mock, &mock,
                           &border_top_bigger_width, &border_top_bigger_height);

    draw_texture(win_surf, BorderTopBigger,
                 win_surf->w / 3 - border_top_bigger_width / 2,
                 GAME_BORDER_TOP - border_top_bigger_height, false);
    draw_texture(win_surf, BorderTopBigger,
                 win_surf->w / 3 * 2 - border_top_bigger_width / 2,
                 GAME_BORDER_TOP - border_top_bigger_height, false);

    // Top corners
    int border_corner_width, border_corner_height;
    get_texture_dimensions(BorderCornerLeft, &mock, &mock, &border_corner_width,
                           &border_corner_height);
    draw_texture(win_surf, BorderCornerLeft,
                 GAME_BORDER_X - border_corner_width,
                 GAME_BORDER_TOP - border_corner_height, false);
    draw_texture(win_surf, BorderCornerRight, win_surf->w - GAME_BORDER_X,
                 GAME_BORDER_TOP - border_corner_height, false);

    int border_side_width, border_side_height;
    get_texture_dimensions(BorderSide, &mock, &mock, &border_side_width,
                           &border_side_height);
    for (int i = GAME_BORDER_TOP; i < win_surf->h; i += border_side_height) {
        // Left
        draw_texture(win_surf, BorderSide, GAME_BORDER_X - border_side_width, i,
                     false);
    }
}

void draw_borders_2(SDL_Surface *win_surf) {
    int mock, border_side_width, border_side_height;
    get_texture_dimensions(BorderSide, &mock, &mock, &border_side_width,
                           &border_side_height);
    for (int i = GAME_BORDER_TOP; i < win_surf->h; i += border_side_height) {
        // Right
        draw_texture(win_surf, BorderSide, win_surf->w - GAME_BORDER_X, i,
                     false);
    }
}

void draw_level(SDL_Surface *win_surf) {
    const Level *level = get_level();
    const int offset_x = (win_surf->w - LEVEL_WIDTH * 32) / 2;
    for (int y = level->offset; y < level->height + level->offset; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            if (level->bricks[y][x].type != EMPTY) {
                int brick_x = offset_x + x * BRICK_WIDTH;
                int brick_y = LEVEL_OFFSET_Y + y * BRICK_HEIGHT;
                draw_brick(win_surf, level->bricks[y][x].type,
                           level->bricks[y][x].current_animation, brick_x,
                           brick_y);
            }
        }
    }
}

void draw_entities(SDL_Surface *win_surf) {
    SpawnedEntities *entities = get_entities();
    for (int i = 0; i < entities->current_entities_count; i++) {
        draw_entity(win_surf, entities->entities[i]);
    }
}

void draw_score(SDL_Surface *win_surf) {
    int score_text_width = draw_red_text(win_surf, "SCORE ", 10, 7);
    draw_integer(win_surf, get_score(), 10 + score_text_width, 7);
    high_score_text_width = draw_red_text(
        win_surf, "HIGH SCORE ",
        win_surf->w - 10 - high_score_value_text_width - high_score_text_width,
        7);
    high_score_value_text_width =
        draw_integer(win_surf, get_high_score(),
                     win_surf->w - 10 - high_score_value_text_width, 7);
}

void draw_lives(SDL_Surface *win_surf, int lives) {
    int mock, ball_width, ball_height, border_width;
    get_texture_dimensions(BallTexture, &mock, &mock, &ball_width,
                           &ball_height);
    get_texture_dimensions(BorderSide, &mock, &mock, &border_width, &mock);

    for (int i = 0; i < lives - 1; i++) {
        draw_texture(win_surf, BallTexture,
                     win_surf->w - GAME_BORDER_X / 2 - ball_width / 2 +
                         border_width / 2,
                     GAME_BORDER_TOP - 10 + ball_height * 1.5 * i, false);
    }
}

void draw(SDL_Surface *win_surf, bool multiplayer_mode, int lives) {
    draw_background(win_surf);

    if (is_end_game()) {
        draw_end_game(win_surf);

    } else {
        draw_borders_1(win_surf);

        draw_level(win_surf);

        draw_entities(win_surf);

        Balls *balls = get_balls();
        for (int i = 0; i < balls->current_balls_count; i++) {
            Ball *ball = &balls->spawned_balls[i];
            draw_texture(win_surf, BallTexture, ball->hit_box.origin.x,
                         ball->hit_box.origin.y, true);
        }

        VAUS *vaus = get_vaus();
        draw_vaus(win_surf, vaus[0], 0);
        if (multiplayer_mode) {
            draw_vaus(win_surf, vaus[1], 1);
            draw_integer(win_surf, 1,
                         vaus[0].hit_box.origin.x + vaus[0].hit_box.width / 2 -
                             8,
                         vaus[0].hit_box.origin.y);
            draw_integer(win_surf, 2,
                         vaus[1].hit_box.origin.x + vaus[1].hit_box.width / 2 -
                             8,
                         vaus[1].hit_box.origin.y);
        }

        draw_borders_2(win_surf);

        draw_lives(win_surf, lives);

        draw_score(win_surf);

        Point active_capsule_point = {GAME_BORDER_X / 2 - 20,
                                      GAME_BORDER_TOP - 10};
        AnimatedEntity active_capsule_display =
            create_entity(get_active_capsule(), active_capsule_point);
        draw_entity(win_surf, active_capsule_display);

        if (lives == 0) {
            dead_text_width = draw_text(win_surf, "Press SPACE to restart",
                                        win_surf->w / 2 - dead_text_width / 2,
                                        win_surf->h / 2);
        }
    }
    if (DEBUG_MODE) {
        draw_text(win_surf, "FPS", 10, win_surf->h - 74);
        draw_integer(win_surf, (int) get_current_fps(), 10, win_surf->h - 42);
    }
}
