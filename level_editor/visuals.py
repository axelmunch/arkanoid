from enum import Enum

import pygame

SPRITE_SHEET = "Arkanoid_sprites.bmp"

BRICK_WIDTH = 32
BRICK_HEIGHT = 16
ANIMATED_BRICK_ANIMATION_FRAMES = 6
ANIMATED_BRICK_ANIMATION_TIME = 8

CAPSULE_WIDTH = 32
CAPSULE_HEIGHT = 16
ANIMATED_CAPSULE_ANIMATION_FRAMES = 8
ANIMATED_CAPSULE_ANIMATION_TIME = 8

THEME_SIZE = 32

bricks_sprites = {}
capsules_sprites = {}
themes_sprites = {}


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


class Theme(Enum):
    def __str__(self):
        return str(self.value)

    THEME_1 = 0
    THEME_2 = 1
    THEME_3 = 2
    THEME_4 = 3
    THEME_5 = 4
    THEME_6 = 5


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
    capsules_sprites[Capsules.EMPTY] = pygame.Surface((0, 0))

    capsules_sprites[Capsules.SLOW] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        capsules_sprites[Capsules.SLOW].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 0,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    capsules_sprites[Capsules.CATCH] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        capsules_sprites[Capsules.CATCH].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 1,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    capsules_sprites[Capsules.EXPAND] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        capsules_sprites[Capsules.EXPAND].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 2,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    capsules_sprites[Capsules.DIVIDE] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        capsules_sprites[Capsules.DIVIDE].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 3,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    capsules_sprites[Capsules.LASER] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        capsules_sprites[Capsules.LASER].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 4,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    capsules_sprites[Capsules.BREAK] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        capsules_sprites[Capsules.BREAK].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 5,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    capsules_sprites[Capsules.ADDITION] = []
    for i in range(ANIMATED_CAPSULE_ANIMATION_FRAMES):
        capsules_sprites[Capsules.ADDITION].append(
            sprites.subsurface(
                256 + CAPSULE_WIDTH * i,
                CAPSULE_HEIGHT * 6,
                CAPSULE_WIDTH,
                CAPSULE_HEIGHT,
            )
        )

    # Themes
    themes_sprites[Theme.THEME_1] = sprites.subsurface(0 + 64 * 0, 128, 64, 64)
    themes_sprites[Theme.THEME_2] = sprites.subsurface(0 + 64 * 1, 128, 64, 64)
    themes_sprites[Theme.THEME_3] = sprites.subsurface(0 + 64 * 2, 128, 64, 64)
    themes_sprites[Theme.THEME_4] = sprites.subsurface(0 + 64 * 3, 128, 64, 64)
    themes_sprites[Theme.THEME_5] = sprites.subsurface(0 + 64 * 4, 128, 64, 64)
    themes_sprites[Theme.THEME_6] = sprites.subsurface(0 + 64 * 5, 128, 64, 64)

    for theme in themes_sprites:
        themes_sprites[theme] = pygame.transform.scale(
            themes_sprites[theme], (THEME_SIZE, THEME_SIZE)
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
    if capsule == Capsules.EMPTY:
        return

    surface.blit(
        capsules_sprites[capsule][
            frame_count
            // ANIMATED_CAPSULE_ANIMATION_TIME
            % ANIMATED_CAPSULE_ANIMATION_FRAMES
        ],
        (x, y),
    )


def draw_theme(surface: pygame.Surface, theme: Theme, x, y):
    surface.blit(themes_sprites[theme], (x, y))
