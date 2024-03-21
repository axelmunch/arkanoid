import pygame
from .visuals import BRICK_WIDTH, BRICK_HEIGHT

GAME_BOARD_WIDTH = 600
GAME_BOARD_HEIGHT = 600
GAME_BOARD_MARGIN_TOP = 50
GAME_BOARD_MARGIN_BOTTOM = 50
GAME_BOARD_MARGIN_LEFT = 20
GAME_BOARD_MARGIN_RIGHT = 20

LEVEL_WIDTH = 13
LEVEL_HEIGHT = 14


game_board = pygame.Surface((GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT))


def is_mouse_hovering(mouse_position: tuple[int, int]) -> bool:
    return is_mouse_hovering_rect(
        mouse_position, (0, 0, GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT)
    )


def is_mouse_hovering_rect(
    mouse_position: tuple[int, int], rect: tuple[int, int, int, int]
) -> bool:
    return (
        mouse_position[0] >= rect[0]
        and mouse_position[0] < rect[0] + rect[2]
        and mouse_position[1] >= rect[1]
        and mouse_position[1] < rect[1] + rect[3]
    )


def update_game_board(
    mouse_position: tuple[int, int], left_click: bool, right_click: bool
):
    if is_mouse_hovering(mouse_position):
        pass

    game_board.fill((192, 64, 64))

    pygame.draw.rect(
        game_board,
        (255, 255, 255),
        (
            GAME_BOARD_MARGIN_LEFT,
            GAME_BOARD_MARGIN_TOP,
            GAME_BOARD_WIDTH - GAME_BOARD_MARGIN_LEFT - GAME_BOARD_MARGIN_RIGHT,
            GAME_BOARD_HEIGHT - GAME_BOARD_MARGIN_TOP - GAME_BOARD_MARGIN_BOTTOM,
        ),
    )

    # Grid
    x_center = (
        GAME_BOARD_MARGIN_LEFT
        + (GAME_BOARD_WIDTH - GAME_BOARD_MARGIN_LEFT - GAME_BOARD_MARGIN_RIGHT) // 2
    )
    y_center = (
        GAME_BOARD_MARGIN_TOP
        + (GAME_BOARD_HEIGHT - GAME_BOARD_MARGIN_TOP - GAME_BOARD_MARGIN_BOTTOM) // 2
    )
    for x in range(LEVEL_WIDTH):
        pygame.draw.line(
            game_board,
            (0, 0, 0),
            (
                x_center - LEVEL_WIDTH * BRICK_WIDTH / 2 + BRICK_WIDTH * x,
                y_center - LEVEL_HEIGHT * BRICK_HEIGHT / 2,
            ),
            (
                x_center - LEVEL_WIDTH * BRICK_WIDTH / 2 + BRICK_WIDTH * x,
                y_center + LEVEL_HEIGHT * BRICK_HEIGHT / 2 - 1,
            ),
        )
    for y in range(LEVEL_HEIGHT):
        pygame.draw.line(
            game_board,
            (0, 0, 0),
            (
                x_center - LEVEL_WIDTH * BRICK_WIDTH / 2,
                y_center - LEVEL_HEIGHT * BRICK_HEIGHT / 2 + BRICK_HEIGHT * y,
            ),
            (
                x_center + LEVEL_WIDTH * BRICK_WIDTH / 2 - 1,
                y_center - LEVEL_HEIGHT * BRICK_HEIGHT / 2 + BRICK_HEIGHT * y,
            ),
        )
    pygame.draw.rect(
        game_board,
        (0, 0, 0),
        (
            x_center - LEVEL_WIDTH * BRICK_WIDTH / 2,
            y_center - LEVEL_HEIGHT * BRICK_HEIGHT / 2,
            LEVEL_WIDTH * BRICK_WIDTH,
            LEVEL_HEIGHT * BRICK_HEIGHT,
        ),
        1,
    )
