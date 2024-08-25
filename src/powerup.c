#include "powerup.h"

// initialize a powerup with type, position and velocity
void powerUp_init(pwrUp_t* p, uint8_t type, vec_t pos, vec_t vel) {

    phyO_init(&p->phyO, POWER_UP_EXTENTS, pos, vel, POWER_UP_DRAG);
    p->type = type;
}



// initializes a random powerup type at the position and with the velocity of the physics object
void powerUp_initRand(pwrUp_t* p, phyO_t* phyO) {

    // randomly generate number
    uint8_t type = rand() % PWR_UP_COUNT;
    powerUp_init(p, type, phyO->pos, phyO->vel);

}

// draws the underlying physics object.
void powerUp_draw(pwrUp_t* p) {

    objectID_t objectID;

    switch (p->type) {

        case PWR_UP_HEART:
        objectID = O_TYPE_PWR_UP_HEART;
        break;

        case PWR_UP_BULLET_SIZE:
        objectID = O_TYPE_PWR_UP_BULLET_SIZE;
        break;

        case PWR_UP_BULLET_BOUNCE:
        objectID = O_TYPE_PWR_UP_BULLET_BOUNCE;
        break;
    }

    // image ids start from O_TYPE_PWR_UP_HEART
    phyO_draw(&p->phyO, p->type + O_TYPE_PWR_UP_HEART);
}

// updates the underlying physics object.
void powerUp_update(pwrUp_t* p) {

    phyO_update(&p->phyO);
}

// apply powerup to the entity
void powerUp_apply(pwrUp_t* p, entity_t* e) {

    if (PWR_UP_HEART == p->type) {

        entity_heal(e);

    } else {

        // make entity take note of the power-up effect.
        e->powerUp = p->type;
    }

    buzzer_play(MELODY_SHOOT); // play a nice sound

    // clear powerup from world
    draw_clearSquare(p->phyO.pos, p->phyO.vel, 8);
    p->phyO.exists = 0;
}

