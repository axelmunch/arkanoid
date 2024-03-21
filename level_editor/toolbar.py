import pygame
from .text import text

TOOLBAR_WIDTH = 350
TOOLBAR_HEIGHT = 600

toolbar = pygame.Surface((TOOLBAR_WIDTH, TOOLBAR_HEIGHT))

load_button_rect = (20, 20, 80, 32)
save_button_rect = (120, 20, 80, 32)


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


def update_toolbar(mouse_position: tuple[int, int], left_click: bool):
    if is_mouse_hovering(mouse_position):
        if left_click:
            # Load
            if is_mouse_hovering_rect(mouse_position, load_button_rect):
                print("Load")
            # Save
            if is_mouse_hovering_rect(mouse_position, save_button_rect):
                print("Save")

    draw_toolbar()


def draw_toolbar():
    toolbar.fill((192, 192, 192))

    # Load button
    pygame.draw.rect(toolbar, (255, 255, 255), load_button_rect)
    pygame.draw.rect(toolbar, (0, 0, 0), load_button_rect, 1)
    text(toolbar, "Load", 40, 30, 24)

    # Save button
    pygame.draw.rect(toolbar, (255, 255, 255), save_button_rect)
    pygame.draw.rect(toolbar, (0, 0, 0), save_button_rect, 1)
    text(toolbar, "Save", 140, 30, 24)
