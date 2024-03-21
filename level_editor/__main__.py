import pygame
from .visuals import load_visuals, Bricks, Capsules, draw_brick, draw_capsule
from .game_board import (
    game_board,
    update_game_board,
    GAME_BOARD_WIDTH,
    GAME_BOARD_HEIGHT,
)
from .toolbar import toolbar, update_toolbar, TOOLBAR_WIDTH, TOOLBAR_HEIGHT
from .text import text

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

    selected_brick, selected_capsule = update_toolbar(
        mouse_position, left_click, frame_count, selected_brick, selected_capsule
    )
    update_game_board(
        (mouse_position[0] - TOOLBAR_WIDTH, mouse_position[1]),
        left_click,
        right_click,
        middle_click,
        selected_brick,
        selected_capsule,
        frame_count,
    )

    window.blit(toolbar, (0, 0))
    window.blit(game_board, (TOOLBAR_WIDTH, 0))

    # FPS
    fps = str(int(clock.get_fps()))
    text(window, f"FPS: {fps}", 10, WINDOW_HEIGHT - 20, 24)

    pygame.display.flip()
