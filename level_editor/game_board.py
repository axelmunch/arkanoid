import pygame

GAME_BOARD_WIDTH = 600
GAME_BOARD_HEIGHT = 600
GAME_BOARD_MARGIN_TOP = 50
GAME_BOARD_MARGIN_BOTTOM = 50
GAME_BOARD_MARGIN_LEFT = 100
GAME_BOARD_MARGIN_RIGHT = 100

LEVEL_WIDTH = 13
LEVEL_MAX_HEIGHT = 14


game_board = pygame.Surface((GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT))


def update_game_board(mouse_position: tuple[int, int]):
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
