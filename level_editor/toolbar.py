import pygame

TOOLBAR_WIDTH = 350
TOOLBAR_HEIGHT = 600

toolbar = pygame.Surface((TOOLBAR_WIDTH, TOOLBAR_HEIGHT))


def update_toolbar(mouse_position: tuple[int, int]):
    toolbar.fill((192, 192, 192))
