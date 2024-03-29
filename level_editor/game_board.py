import pygame

from .files import select_file_load, select_file_save
from .text import text
from .visuals import BRICK_HEIGHT, BRICK_WIDTH, Bricks, Capsules, Theme, draw_brick

GAME_BOARD_WIDTH = 600
GAME_BOARD_HEIGHT = 600
GAME_BOARD_MARGIN_TOP = 150
GAME_BOARD_MARGIN_BOTTOM = 200
GAME_BOARD_MARGIN_LEFT = 10
GAME_BOARD_MARGIN_RIGHT = 10

LEVEL_WIDTH = 13
LEVEL_HEIGHT = 14


game_board = pygame.Surface((GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT))


class Level:
    def __init__(self):
        self.theme = Theme.THEME_1

        self.offset = 0
        self.height = 1

        self.bricks = []

        self.clear()

    def place(self, brick: tuple[Bricks, Capsules], x, y):
        self.bricks[y][x] = brick
        self.update()

    def remove(self, x, y):
        self.bricks[y][x] = (Bricks.EMPTY, Capsules.EMPTY)
        self.update()

    def remove_capsule(self, x, y):
        brick, _ = self.bricks[y][x]
        if brick == Bricks.EMPTY:
            return
        self.bricks[y][x] = (brick, Capsules.EMPTY)
        self.update()

    def set_theme(self, theme: Theme):
        self.theme = theme

    def clear(self):
        self.bricks = [
            [(Bricks.EMPTY, Capsules.EMPTY) for _ in range(LEVEL_WIDTH)]
            for _ in range(LEVEL_HEIGHT)
        ]

        self.update()

    def update(self):
        self.offset = 0
        offset_found = False
        for y in range(LEVEL_HEIGHT):
            for x in range(LEVEL_WIDTH):
                if self.bricks[y][x][0] != Bricks.EMPTY and not offset_found:
                    self.offset = y
                    offset_found = True

        last_line_with_data = self.offset
        for y in range(self.offset, LEVEL_HEIGHT):
            for x in range(LEVEL_WIDTH):
                if self.bricks[y][x][0] != Bricks.EMPTY:
                    last_line_with_data = y
                    break
        self.height = last_line_with_data - self.offset + 1


def save_level(level: Level):
    filename = select_file_save()
    if filename is None or filename == "":
        return

    with open(filename, "w") as file:
        write_text = ""
        write_text += f"{level.theme}\n"
        write_text += f"{level.offset}\n"
        write_text += f"{level.height}\n"
        for y in range(level.offset, level.offset + level.height):
            for x in range(LEVEL_WIDTH):
                brick, capsule = level.bricks[y][x]
                write_text += f"{str(brick.value)}\n{str(capsule.value)}\n"
        file.write(write_text[:-1])


def load_level(filename):
    filename = select_file_load()
    if filename is None or filename == "":
        return

    level = Level()

    with open(filename, "r") as file:
        level.theme = Theme(int(file.readline()))
        level.offset = int(file.readline())
        level.height = int(file.readline())

        for i in range(level.height * LEVEL_WIDTH):
            brick = Bricks(int(file.readline()))
            capsule = Capsules(int(file.readline()))
            level.bricks[i // LEVEL_WIDTH + level.offset][i % LEVEL_WIDTH] = (
                brick,
                capsule,
            )

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


def update_game_board(
    mouse_position: tuple[int, int],
    left_click: bool,
    right_click: bool,
    middle_click: bool,
    selected_brick,
    selected_capsule,
    level: Level,
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
                level.place((selected_brick, selected_capsule), x, y)
        if right_click:
            # Remove brick
            if 0 <= x < LEVEL_WIDTH and 0 <= y < LEVEL_HEIGHT:
                level.remove(x, y)
        if middle_click:
            # Remove capsule
            level.remove_capsule(x, y)

    draw_game_board(level, frame_count)


def draw_game_board(level, frame_count):
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
