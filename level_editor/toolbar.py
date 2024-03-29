import pygame

from .text import text
from .visuals import (
    BRICK_HEIGHT,
    BRICK_WIDTH,
    CAPSULE_HEIGHT,
    CAPSULE_WIDTH,
    THEME_SIZE,
    Bricks,
    Capsules,
    Theme,
    draw_brick,
    draw_capsule,
    draw_theme,
)

TOOLBAR_WIDTH = 350
TOOLBAR_HEIGHT = 600

toolbar = pygame.Surface((TOOLBAR_WIDTH, TOOLBAR_HEIGHT))

load_button_rect = (20, 20, 80, 32)
save_button_rect = (120, 20, 80, 32)
clear_button_rect = (220, 20, 80, 32)

elements_by_line = 4
elements_space_x = 50
elements_space_y = 30
bricks_start_y = 250
capsules_start_y = 460
themes_start_y = 100
elements_start_x = (
    TOOLBAR_WIDTH / 2
    - (
        elements_by_line * (max(BRICK_WIDTH, CAPSULE_WIDTH) + elements_space_x)
        - elements_space_x
    )
    / 2
)


def is_mouse_hovering(mouse_position: tuple[int, int]) -> bool:
    return is_mouse_hovering_rect(mouse_position, (0, 0, TOOLBAR_WIDTH, TOOLBAR_HEIGHT))


def is_mouse_hovering_rect(
    mouse_position: tuple[int, int], rect: tuple[int, int, int, int]
) -> bool:
    return (
        mouse_position[0] >= rect[0]
        and mouse_position[0] < rect[0] + rect[2]
        and mouse_position[1] >= rect[1]
        and mouse_position[1] < rect[1] + rect[3]
    )


def update_toolbar(
    mouse_position: tuple[int, int],
    left_click: bool,
    frame_count,
    selected_brick,
    selected_capsule,
    selected_theme,
):
    event_load = False
    event_save = False
    event_clear = False

    if is_mouse_hovering(mouse_position):
        if left_click:
            # Load
            if is_mouse_hovering_rect(mouse_position, load_button_rect):
                event_load = True
            # Save
            if is_mouse_hovering_rect(mouse_position, save_button_rect):
                event_save = True
            # Clear
            if is_mouse_hovering_rect(mouse_position, clear_button_rect):
                event_clear = True

            # Select brick
            for i, brick in enumerate(Bricks):
                x = elements_start_x + i % elements_by_line * (
                    BRICK_WIDTH + elements_space_x
                )
                y = bricks_start_y + i // elements_by_line * (
                    BRICK_HEIGHT + elements_space_y
                )
                if is_mouse_hovering_rect(
                    mouse_position, (x, y, BRICK_WIDTH, BRICK_HEIGHT)
                ):
                    selected_brick = brick

            # Select capsule
            for i, capsule in enumerate(Capsules):
                x = elements_start_x + i % elements_by_line * (
                    CAPSULE_WIDTH + elements_space_x
                )
                y = capsules_start_y + i // elements_by_line * (
                    CAPSULE_HEIGHT + elements_space_y
                )
                if is_mouse_hovering_rect(
                    mouse_position, (x, y, CAPSULE_WIDTH, CAPSULE_HEIGHT)
                ):
                    selected_capsule = capsule

            # Select theme
            for i, theme in enumerate(Theme):
                x = elements_start_x + i % elements_by_line * (
                    THEME_SIZE + elements_space_x
                )
                y = themes_start_y + i // elements_by_line * (
                    THEME_SIZE + elements_space_y
                )
                if is_mouse_hovering_rect(
                    mouse_position, (x, y, THEME_SIZE, THEME_SIZE)
                ):
                    selected_theme = theme

    draw_toolbar(selected_brick, selected_capsule, selected_theme, frame_count)

    return (
        selected_brick,
        selected_capsule,
        selected_theme,
        event_load,
        event_save,
        event_clear,
    )


def draw_toolbar(selected_brick, selected_capsule, selected_theme, frame_count):
    toolbar.fill((192, 192, 192))

    # Load button
    pygame.draw.rect(toolbar, (255, 255, 255), load_button_rect)
    pygame.draw.rect(toolbar, (0, 0, 0), load_button_rect, 1)
    text(toolbar, "Load", 40, 30, 24)

    # Save button
    pygame.draw.rect(toolbar, (255, 255, 255), save_button_rect)
    pygame.draw.rect(toolbar, (0, 0, 0), save_button_rect, 1)
    text(toolbar, "Save", 140, 30, 24)

    # Clear button
    pygame.draw.rect(toolbar, (255, 255, 255), clear_button_rect)
    pygame.draw.rect(toolbar, (0, 0, 0), clear_button_rect, 1)
    text(toolbar, "Clear", 240, 30, 24)

    # Bricks
    for i, brick in enumerate(Bricks):
        x = elements_start_x + i % elements_by_line * (BRICK_WIDTH + elements_space_x)
        y = bricks_start_y + i // elements_by_line * (BRICK_HEIGHT + elements_space_y)
        draw_brick(
            toolbar,
            brick,
            x,
            y,
            frame_count,
        )
        if selected_brick == brick:
            pygame.draw.rect(
                toolbar,
                (255, 0, 0),
                (x - 4, y - 4, BRICK_WIDTH + 8, BRICK_HEIGHT + 8),
                2,
            )

    # Capsules
    for i, capsule in enumerate(Capsules):
        x = elements_start_x + i % elements_by_line * (CAPSULE_WIDTH + elements_space_x)
        y = capsules_start_y + i // elements_by_line * (
            CAPSULE_HEIGHT + elements_space_y
        )
        draw_capsule(
            toolbar,
            capsule,
            x,
            y,
            frame_count,
        )
        text(toolbar, capsule.name, x, y + CAPSULE_HEIGHT + 5, 14)
        if selected_capsule == capsule:
            pygame.draw.rect(
                toolbar,
                (255, 0, 0),
                (x - 4, y - 4, CAPSULE_WIDTH + 8, CAPSULE_HEIGHT + 8),
                2,
            )

    # Themes
    for i, theme in enumerate(Theme):
        x = elements_start_x + i % elements_by_line * (THEME_SIZE + elements_space_x)
        y = themes_start_y + i // elements_by_line * (THEME_SIZE + elements_space_y)
        draw_theme(
            toolbar,
            theme,
            x,
            y,
        )
        if selected_theme == theme:
            pygame.draw.rect(
                toolbar,
                (255, 0, 0),
                (x - 4, y - 4, THEME_SIZE + 8, THEME_SIZE + 8),
                2,
            )
