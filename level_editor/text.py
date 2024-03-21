import pygame

pygame.init()
font = pygame.font.SysFont(None, 24)


def text(window, value: str, x, y, color=(0, 0, 0)):
    text = font.render(value, True, color)
    window.blit(text, (x, y))
