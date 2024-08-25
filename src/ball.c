
#include "ball.h"
#include "math.h"

#define FIX14_MULT(a, b) ( ((a >> 4) * (b >> 4)) >> 6 )


void ball_draw(ball_t* b) {

    gotoXY(conv1814to3200(b->position.x), conv1814to3200(b->position.y));
    printf("%c", b->symbol);
}

void ball_move(ball_t* ball, int32_t delta) {

    ball->position.x += FIX14_MULT(ball->velocity.x, delta);
    ball->position.y += FIX14_MULT(ball->velocity.y, delta);
}


void ball_checkCollisions(ball_t* b, hitbox_t* h) {

    if (b->position.x <= h->wallLeft) {
        b->velocity.x = -b->velocity.x;
        b->velocity.y = -b->velocity.y;

    } else if (b->position.x >= h->wallRight) {
        b->velocity.x = -b->velocity.x;
        b->velocity.y = -b->velocity.y;
    } else if (b->position.y <= h->wallTop) {
        b->velocity.x = -b->velocity.x;
        b->velocity.y = -b->velocity.y;
    } else if (b->position.y >= h->wallBot) {
        b->velocity.x = -b->velocity.x;
        b->velocity.y = -b->velocity.y;
    }
}

