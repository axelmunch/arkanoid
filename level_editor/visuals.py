import pygame
from enum import Enum


SPRITE_SHEET = "Arkanoid_sprites.bmp"

BRICK_WIDTH = 32
BRICK_HEIGHT = 16
ANIMATED_BRICK_ANIMATION_FRAMES = 6
ANIMATED_BRICK_ANIMATION_TIME = 8

CAPSULE_WIDTH = 32
CAPSULE_HEIGHT = 16
ANIMATED_CAPSULE_ANIMATION_FRAMES = 8
ANIMATED_CAPSULE_ANIMATION_TIME = 8

bricks_sprites = {}
Capsules_sprites = {}


class Bricks(Enum):
    def __str__(self):
        return str(self.value)

    EMPTY = 0
    WHITE = 1
    ORANGE = 2
    CYAN = 3
    LIME = 4
    DARK_BLUE = 5
    GREEN = 6
    RED = 7
    BLUE = 8
    PINK = 9
    YELLOW = 10
    DARK_RED = 11
    OCEAN_BLUE = 12
    METAL = 13
    GOLD = 14


class Capsules(Enum):
    def __str__(self):
        return str(self.value)

    EMPTY = 0
    SLOW = 1
    CATCH = 2
    EXPAND = 3
    DIVIDE = 4
    LASER = 5
    BREAK = 6
    ADDITION = 7


def load_visuals():
    sprites = pygame.image.load(SPRITE_SHEET).convert()

    # Bricks
    bricks_sprites[Bricks.EMPTY] = pygame.Surface((0, 0))

    bricks_sprites[Bricks.WHITE] = sprites.subsurface(
        BRICK_WIDTH * 0, BRICK_HEIGHT * 0, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.ORANGE] = sprites.subsurface(
        BRICK_WIDTH * 1, BRICK_HEIGHT * 0, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.CYAN] = sprites.subsurface(
        BRICK_WIDTH * 2, BRICK_HEIGHT * 0, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.LIME] = sprites.subsurface(
        BRICK_WIDTH * 3, BRICK_HEIGHT * 0, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.DARK_BLUE] = sprites.subsurface(
        BRICK_WIDTH * 4, BRICK_HEIGHT * 0, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.GREEN] = sprites.subsurface(
        BRICK_WIDTH * 5, BRICK_HEIGHT * 0, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.RED] = sprites.subsurface(
        BRICK_WIDTH * 0, BRICK_HEIGHT * 1, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.BLUE] = sprites.subsurface(
        BRICK_WIDTH * 1, BRICK_HEIGHT * 1, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.PINK] = sprites.subsurface(
        BRICK_WIDTH * 2, BRICK_HEIGHT * 1, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.YELLOW] = sprites.subsurface(
        BRICK_WIDTH * 3, BRICK_HEIGHT * 1, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.DARK_RED] = sprites.subsurface(
        BRICK_WIDTH * 4, BRICK_HEIGHT * 1, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.OCEAN_BLUE] = sprites.subsurface(
        BRICK_WIDTH * 5, BRICK_HEIGHT * 1, BRICK_WIDTH, BRICK_HEIGHT
    )

    bricks_sprites[Bricks.METAL] = []
    for i in range(ANIMATED_BRICK_ANIMATION_FRAMES):
        bricks_sprites[Bricks.METAL].append(
            sprites.subsurface(
                BRICK_WIDTH * i, BRICK_HEIGHT * 2, BRICK_WIDTH, BRICK_HEIGHT
            )
        )
    bricks_sprites[Bricks.GOLD] = []
    for i in range(ANIMATED_BRICK_ANIMATION_FRAMES):
        bricks_sprites[Bricks.GOLD].append(
            sprites.subsurface(
                BRICK_WIDTH * i, BRICK_HEIGHT * 3, BRICK_WIDTH, BRICK_HEIGHT
            )
        )

    # Capsules
    Capsules_sprites[Capsules.EMPTY] = pygame.Surface((0, 0))

    Capsules_sprites[Capsules.SLOW] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        Capsules_sprites[Capsules.SLOW].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 0,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    Capsules_sprites[Capsules.CATCH] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        Capsules_sprites[Capsules.CATCH].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 1,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    Capsules_sprites[Capsules.EXPAND] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        Capsules_sprites[Capsules.EXPAND].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 2,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    Capsules_sprites[Capsules.DIVIDE] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        Capsules_sprites[Capsules.DIVIDE].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 3,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    Capsules_sprites[Capsules.LASER] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        Capsules_sprites[Capsules.LASER].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 4,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    Capsules_sprites[Capsules.BREAK] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        Capsules_sprites[Capsules.BREAK].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 5,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    Capsules_sprites[Capsules.ADDITION] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        Capsules_sprites[Capsules.ADDITION].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 6,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )


def draw_brick(surface: pygame.Surface, brick: Bricks, x, y, frame_count):

    if brick == Bricks.METAL:
        surface.blit(
            bricks_sprites[Bricks.METAL][
                frame_count
                // ANIMATED_BRICK_ANIMATION_TIME
                % ANIMATED_BRICK_ANIMATION_FRAMES
            ],
            (x, y),
        )
    elif brick == Bricks.GOLD:
        surface.blit(
            bricks_sprites[Bricks.GOLD][
                frame_count
                // ANIMATED_BRICK_ANIMATION_TIME
                % ANIMATED_BRICK_ANIMATION_FRAMES
            ],
            (x, y),
        )
    else:
        surface.blit(bricks_sprites[brick], (x, y))


def draw_capsule(surface: pygame.Surface, capsule: Capsules, x, y, frame_count):
    surface.blit(
        Capsules_sprites[capsule][
            frame_count
            // ANIMATED_CAPSULE_ANIMATION_TIME
            % ANIMATED_CAPSULE_ANIMATION_FRAMES
        ],
        (x, y),
    )
