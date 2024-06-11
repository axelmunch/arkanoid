#ifndef ARKANOID_TEXT_H
#define ARKANOID_TEXT_H

#include <SDL.h>
#include <stdbool.h>

void init_text();
int draw_red_text(SDL_Surface *surface, char *text, int x, int y);
int draw_text(SDL_Surface *surface, char *text, int x, int y);
int draw_integer(SDL_Surface *surface, int number, int x, int y);
int draw_number(SDL_Surface *surface, double number, int x, int y);
int draw_char(SDL_Surface *surface, char c, int x, int y, bool color_red);
void char_position_on_sprite(char c, int *x, int *y);

#endif // ARKANOID_TEXT_H
