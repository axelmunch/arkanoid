#ifndef ARKANOID_CONFIG_H
#define ARKANOID_CONFIG_H

#define DEBUG_MODE true

#define GAME_FPS    60
#define GAME_FPS_MS (1000 / GAME_FPS)
#define FPS_TARGET  60

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600

#define VAUS_MAX_SIZE             8
#define ANIMATION_TIMER_MS        150
#define DIRECTION_CHANGE_TIMER_MS 500
#define SHOOT_RELOAD_TIME_MS      500
#define CATCH_BALL_RELOAD_TIME_MS 200

#define BALL_EFFECT           25
#define DEFAULT_BALL_VELOCITY 7.0

#define MAX_LEVELS 15

#define LEVEL_OFFSET_Y 150
#define LEVEL_WIDTH    13
#define LEVEL_HEIGHT   16

#define BRICK_WIDTH  32
#define BRICK_HEIGHT 16

#define GAME_BORDER_TOP 50
#define GAME_BORDER_X   (SCREEN_WIDTH - BRICK_WIDTH * LEVEL_WIDTH) / 2

#define MAX_ENTITIES 50

#define DISPLAY_SHADOWS true
#define SHADOW_OFFSET   5
#define SHADOW_ALPHA    128

#define DEFAULT_LIVES 2

#define ASSETS_PATH "../assets"
#define LEVELS_PATH "../levels"

#define CHUNK_COUNT   14
#define CHUNK_VOLUME  8
#define MUSIC_VOLUME  16
#define CHANNEL_COUNT 16

#endif // ARKANOID_CONFIG_H