
#include "math.h"

#ifndef BALL_H
#define BALL_H

typedef struct {
    vec_t position;
    vec_t velocity;
    char symbol;
} ball_t;

typedef struct {
    int wallLeft, wallRight, wallTop, wallBot;
} hitbox_t;

void ball_draw(ball_t* b);

void ball_move(ball_t* ball, int32_t delta);

void ball_checkCollisions(ball_t* b, hitbox_t* h);

#endif
