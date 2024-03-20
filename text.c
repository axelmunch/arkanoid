#include "text.h"
#include <math.h>
#include <stdbool.h>

int char_width = 32;
int char_height = 32;
int char_width_in_cell = 18;
int char_by_line = 16;
char *font_file = "Arkanoid_ascii.bmp";
char *font_characters = " !\"#$%&'()*+,-./"
                        "0123456789:;<=>?"
                        "@ABCDEFGHIJKLMNO"
                        "PQRSTUVWXYZ[\\]^_"
                        "`abcdefghijklmno"
                        "pqrstuvwxyz{|}~ ";

SDL_Surface *text_bitmap = NULL;

void init_text() {
    text_bitmap = SDL_LoadBMP(font_file);
    SDL_SetColorKey(text_bitmap, true, 0);
}

int draw_text(SDL_Surface *surface, char *text, int x, int y) {
    int text_width = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        text_width +=
            draw_char(surface, text[i], x + i * char_width_in_cell, y);
    }

    return text_width;
}

int draw_integer(SDL_Surface *surface, int number, int x, int y) {
    int size = snprintf(NULL, 0, "%d", number);
    char number_str[size];
    sprintf(number_str, "%d", number);

    return draw_text(surface, number_str, x, y);
}

int draw_number(SDL_Surface *surface, double number, int x, int y) {
    int size = snprintf(NULL, 0, "%lf", number);
    char number_str[size];
    sprintf(number_str, "%lf", number);

    return draw_text(surface, number_str, x, y);
}

int draw_char(SDL_Surface *surface, char c, int x, int y) {
    int char_x, char_y;
    char_position_on_sprite(c, &char_x, &char_y);
    SDL_Rect src = {char_x, char_y, char_width_in_cell, char_height};
    SDL_Rect dst = {x, y, 0, 0};
    SDL_BlitSurface(text_bitmap, &src, surface, &dst);

    return char_width_in_cell;
}

void char_position_on_sprite(char c, int *x, int *y) {
    int pos = strchr(font_characters, c) - font_characters;
    if (pos < 0) {
        *x = 0;
        *y = 0;
    }
    *x = (pos % char_by_line) * char_width;
    *y = (pos / char_by_line) * char_height;
}
