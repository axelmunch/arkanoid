import pygame

from .game_board import (
    GAME_BOARD_HEIGHT,
    GAME_BOARD_WIDTH,
    Level,
    game_board,
    load_level,
    save_level,
    update_game_board,
)
from .text import text
from .toolbar import TOOLBAR_HEIGHT, TOOLBAR_WIDTH, toolbar, update_toolbar
from .visuals import Bricks, Capsules, Theme, load_visuals

WINDOW_WIDTH = TOOLBAR_WIDTH + GAME_BOARD_WIDTH
WINDOW_HEIGHT = max(TOOLBAR_HEIGHT, GAME_BOARD_HEIGHT)

pygame.init()
window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("Arkanoid Level Editor")
clock = pygame.time.Clock()


running = True
frame_count = 0


# Init
load_visuals()

selected_brick = Bricks.WHITE
selected_capsule = Capsules.EMPTY
selected_theme = Theme.THEME_1
level = Level()

while running:
    clock.tick(60)

    frame_count = (frame_count + 1) % 10000

    left_click = False
    right_click = False
    middle_click = False

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False

        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                left_click = True
            if event.button == 3:
                right_click = True
            if event.button == 2:
                middle_click = True

    mouse_position = pygame.mouse.get_pos()

    (
        selected_brick,
        selected_capsule,
        selected_theme,
        event_load,
        event_save,
        event_clear,
    ) = update_toolbar(
        mouse_position,
        left_click,
        frame_count,
        selected_brick,
        selected_capsule,
        selected_theme,
    )

    level.set_theme(selected_theme)

    if event_load:
        loaded_data = load_level()
        if loaded_data is not None:
            level = loaded_data
            selected_theme = level.theme
    if event_save:
        save_level(level)
    if event_clear:
        level.clear()

    update_game_board(
        (mouse_position[0] - TOOLBAR_WIDTH, mouse_position[1]),
        left_click,
        right_click,
        middle_click,
        selected_brick,
        selected_capsule,
        level,
        frame_count,
    )

    window.blit(toolbar, (0, 0))
    window.blit(game_board, (TOOLBAR_WIDTH, 0))

    # FPS
    fps = str(int(clock.get_fps()))
    text(window, f"FPS: {fps}", 10, WINDOW_HEIGHT - 20, 24)

    pygame.display.flip()
