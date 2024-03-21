import pygame

pygame.init()

fonts = {}


def text(window, value: str, x, y, size, color=(0, 0, 0)):
    if size not in fonts:
        fonts[size] = pygame.font.SysFont(None, size)

    text = fonts[size].render(value, True, color)
    window.blit(text, (x, y))
