#include "score.h"

int score;

void reset_score() { score = 0; }

void add_score(int value) { score += value; }

void break_brick(BrickType brick_type) {
    switch (brick_type) {
    case ORANGE:
    case YELLOW:
    case CYAN:
    case BLUE:
    case DARK_BLUE: {
        add_score(50);
        break;
    }
    case RED:
    case DARK_RED:
    case PINK: {
        add_score(70);
        break;
    }
    case OCEAN_BLUE:
    case LIME:
    case GREEN: {
        add_score(80);
        break;
    }
    case WHITE: {
        add_score(100);
        break;
    }
    case METAL: {
        add_score(120);
        break;
    }
    default:
        break;
    }
}

int get_score() { return score; }
