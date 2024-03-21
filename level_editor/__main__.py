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


class Level:
    def __init__(self):
        self.offset = 0
        self.height = 1
        self.bricks = []


def save_level(level: Level, filename):
    with open(filename, "w") as file:
        file.write(f"{level.offset}\n")
        file.write(f"{level.height}\n")
        for brick in level.bricks:
            file.write(f"{brick[0]} {brick[1]}\n")


def load_level(filename):
    level = Level()

    with open(filename, "r") as file:
        level.offset = int(file.readline())
        level.height = int(file.readline())
        for line in file:
            x, y = map(int, line.split())
            level.bricks.append((x, y))

    return level


# Init
load_visuals()

while running:
    clock.tick(60)

    frame_count = (frame_count + 1) % 10000

    left_click = False
    right_click = False

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

    mouse_position = pygame.mouse.get_pos()

    update_toolbar(mouse_position, left_click, right_click)
    update_game_board(
        (mouse_position[0] - TOOLBAR_WIDTH, mouse_position[1]), left_click, right_click
    )

    window.fill((255, 255, 255))

    window.blit(toolbar, (0, 0))
    window.blit(game_board, (TOOLBAR_WIDTH, 0))

    # FPS
    fps = str(int(clock.get_fps()))
    text(window, f"FPS: {fps}", 10, WINDOW_HEIGHT - 20)

    draw_brick(window, Bricks.WHITE, 100, 100, frame_count)
    draw_brick(window, Bricks.METAL, 132, 100, frame_count)
    draw_brick(window, Bricks.GOLD, 164, 100, frame_count)
    draw_capsule(window, Capsules.LASER, 196, 100, frame_count)

    pygame.display.flip()
