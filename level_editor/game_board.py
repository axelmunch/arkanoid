import pygame
from .visuals import Bricks, Capsules, BRICK_WIDTH, BRICK_HEIGHT, draw_brick
from .text import text

GAME_BOARD_WIDTH = 600
GAME_BOARD_HEIGHT = 600
GAME_BOARD_MARGIN_TOP = 50
GAME_BOARD_MARGIN_BOTTOM = 50
GAME_BOARD_MARGIN_LEFT = 50
GAME_BOARD_MARGIN_RIGHT = 50

LEVEL_WIDTH = 13
LEVEL_HEIGHT = 14


game_board = pygame.Surface((GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT))


class Level:
    def __init__(self):
        self.bricks = [
            [(Bricks.EMPTY, Capsules.EMPTY) for x in range(LEVEL_WIDTH)]
            for y in range(LEVEL_HEIGHT)
        ]

        self.update()

    def place(self, brick: Bricks, x, y):
        self.bricks[y][x] = brick

    def remove(self, x, y):
        self.bricks[y][x] = (Bricks.EMPTY, Capsules.EMPTY)

    def set_capsule(self, capsule: Capsules, x, y):
        brick, _ = self.bricks[y][x]
        if brick == Bricks.EMPTY:
            return
        self.bricks[y][x] = (brick, capsule)

    def update(self):
        self.offset = 0
        for y in range(LEVEL_HEIGHT):
            for x in range(LEVEL_WIDTH):
                if self.bricks[y][x][0] != Bricks.EMPTY:
                    self.offset = max(self.offset, y)

        last_line_with_data = self.offset
        for y in range(self.offset, LEVEL_HEIGHT):
            for x in range(LEVEL_WIDTH):
                if self.bricks[y][x][0] != Bricks.EMPTY:
                    last_line_with_data = y
        self.height = min(last_line_with_data - self.offset, 1)


def save_level(level: Level, filename):
    with open(filename, "w") as file:
        file.write(f"{level.offset}\n")
        file.write(f"{level.height}\n")
        for brick in level.bricks:
            file.write(f"{brick[0]} {brick[1]}\n")


def load_level(filename):
    with open(filename, "r") as file:
        for line in file:
            x, y = map(int, line.split())
            level.bricks.append((x, y))

    return level


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


level = Level()


def update_game_board(
    mouse_position: tuple[int, int],
    left_click: bool,
    right_click: bool,
    frame_count,
):
    if is_mouse_hovering(mouse_position):
        x_center = (
            GAME_BOARD_MARGIN_LEFT
            + (GAME_BOARD_WIDTH - GAME_BOARD_MARGIN_LEFT - GAME_BOARD_MARGIN_RIGHT) // 2
        )
        y_center = (
            GAME_BOARD_MARGIN_TOP
            + (GAME_BOARD_HEIGHT - GAME_BOARD_MARGIN_TOP - GAME_BOARD_MARGIN_BOTTOM)
            // 2
        )
        x = (
            mouse_position[0] - x_center + LEVEL_WIDTH * BRICK_WIDTH // 2
        ) // BRICK_WIDTH
        y = (
            mouse_position[1] - y_center + LEVEL_HEIGHT * BRICK_HEIGHT // 2
        ) // BRICK_HEIGHT
        if left_click:
            # Place brick
            if 0 <= x < LEVEL_WIDTH and 0 <= y < LEVEL_HEIGHT:
                level.place((Bricks.GOLD, Capsules.EXPAND), x, y)
        if right_click:
            # Remove brick
            if 0 <= x < LEVEL_WIDTH and 0 <= y < LEVEL_HEIGHT:
                level.remove(x, y)

    draw_game_board(frame_count)


def draw_game_board(frame_count):
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

    # Bricks
    for y in range(LEVEL_HEIGHT):
        for x in range(LEVEL_WIDTH):
            brick, capsule = level.bricks[y][x]
            if brick != Bricks.EMPTY:
                draw_brick(
                    game_board,
                    brick,
                    x_center - LEVEL_WIDTH * BRICK_WIDTH // 2 + x * BRICK_WIDTH,
                    y_center - LEVEL_HEIGHT * BRICK_HEIGHT // 2 + y * BRICK_HEIGHT,
                    frame_count,
                )
                if capsule != Capsules.EMPTY:
                    text(
                        game_board,
                        capsule.name,
                        x_center - LEVEL_WIDTH * BRICK_WIDTH // 2 + x * BRICK_WIDTH,
                        y_center
                        - LEVEL_HEIGHT * BRICK_HEIGHT // 2
                        + y * BRICK_HEIGHT
                        + BRICK_HEIGHT // 3,
                        11,
                        (0, 0, 0),
                    )
