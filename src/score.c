#include "score.h"

char *high_score_file = "high_score.ark";

int score;
int high_score;

void init_score() {
    score = 0;
    load_high_score();
}

void reset_score() {
    if (score >= high_score) {
        save_high_score();
    }
    score = 0;
}

void add_score(int value) {
    score += value;
    update_score();
}

void update_score() {
    if (score > high_score) {
        high_score = score;
    }
}

void score_break_brick(BrickType brick_type) {
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

int get_high_score() { return high_score; }

void load_high_score() {
    FILE *file = fopen(high_score_file, "r");
    if (file == NULL) {
        high_score = 0;
        return;
    }
    int return_code = fscanf(file, "%d", &high_score);
    fclose(file);
}

void save_high_score() {
    FILE *file = fopen(high_score_file, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", high_score_file);
        exit(1);
    }
    fprintf(file, "%d", high_score);
    fclose(file);
}
