
#include "bullet.h"

// initializes a new bullet
void bullet_init(bullet_t* bullet, uint8_t type, uint8_t player, vec_t pos, fixP_t angle) {

    bullet->data = 0;
    bullet->data |= type; // bit 0 and 1 store the bullets type
    bullet->data |= (player << 2);  // bit 2 stores the player that fired the bullet (0 = player 1, 1 = player 2)

    // convert the rotation into a 512 step of a circle (to use in LUTsin)
    int step = fixToInt(FIX14_DIV(angle, ROTATION_STEP) * 32);
    vec_t vel;
    // accelerate in rotation direction
    vec_init(&vel, FIX14_MULT(BULLET_SPEED, cosine(step)), FIX14_MULT(BULLET_SPEED, -sine(step)));

    fixP_t extents;
    fixP_t drag;

    switch (type) {

        case BULLET_TYPE_NORMAL:
        bullet->duration = 100;
        extents = 2 << 14;
        drag = BULLET_DRAG_NORMAL;
        break;

        case BULLET_TYPE_LARGE:
        bullet->duration = 200;
        extents = 4 << 14;
        drag = BULLET_DRAG_NORMAL;
        break;

        case BULLET_TYPE_BOUNCE:
        bullet->duration = 300;
        extents = 2 << 14;
        drag = BULLET_DRAG_NONE;
        break;
    }

    // initialize underlying physics object
    phyO_init(&bullet->phyO, extents, pos, vel, drag);
}

// updates this bullet and the underlying physics object
void bullet_update(bullet_t* bullet) {


    if (bullet->phyO.exists) {

        // moves the bullet by its velocity
        phyO_update(&bullet->phyO);

        // kill bullet if it is alive for too long
        if (bullet->duration > 0) {

            bullet->duration--;

        } else if (0 == bullet->duration) {

            bullet->phyO.exists = 0;

            // extract the bullet type and set bullet clear area accordingly
            uint8_t clearSize = (bullet->data & 0b00000011 == BULLET_TYPE_LARGE) ? BULLET_SIZE_LARGE : BULLET_SIZE_NORMAL;
            draw_clearSquare(bullet->phyO.pos, bullet->phyO.vel, clearSize);
            world_clearScreen();
        }
    }
}

// draws the underlying physics object
void bullet_draw(bullet_t* bullet) {

    if (bullet->phyO.exists) {

        draw_bullet(bullet->phyO.pos, bullet->phyO.vel, bullet->data & 0b11);
    }
}

// function for handling a bullet that is colliding
void bullet_colliding(bullet_t* bullet) {

    if (bullet->phyO.exists) {

        bullet->phyO.exists = 0;

        // extract the bullet type and set bullet clear area accordingly
        uint8_t clearSize = (bullet->data & 0b00000011 == BULLET_TYPE_LARGE) ? BULLET_SIZE_LARGE : BULLET_SIZE_NORMAL;
        draw_clearSquare(bullet->phyO.pos, bullet->phyO.vel, clearSize);
        world_clearScreen();
    }
}
