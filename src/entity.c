
#include "entity.h"


// initializes the entity with collision extents, position, velocity, air resistance, rotation and maximum health.
void entity_init(entity_t* e, fixP_t extents, vec_t pos, vec_t vel, fixP_t drag, fixP_t rotation, uint8_t maxHealth) {

    // initialize underlying physics object
    phyO_init(&e->phyO, extents, pos, vel, drag);

    e->rotation = rotation;
    e->powerUp = 0; // spawn with no power-up
    e->maxHealth = maxHealth;
    e->health = e->maxHealth; // entities spawn with full health
    e->damageFrame = 0; // spawn with damage animation off.
}

// draws the entity at the entities position
void entity_draw(entity_t* e, entityID_t entityType) {

    // check if entity is alive.
    if (!e->phyO.exists) {
        return;
    }

    // change color if entity is taking damage.
    if (e->damageFrame % 2) {

        fgcolor(6); // draw in blue.

    } else {

        // change color dependent on entity type
        switch (entityType) {

            case E_TYPE_PLAYER:
            fgcolor(15); // use white for player
            break;

            default:
            fgcolor(1); // use red by default
        }
    }

    // convert entity rotation to a rotation index in the LUT.
    rot_t rotIdx = fixToInt(FIX14_DIV(e->rotation, ROTATION_STEP));
    draw_entityImg(entityType, rotIdx, e->phyO.pos, e->phyO.vel);
}

// increments entity rotation by angle
void entity_rotate(entity_t* e, fixP_t r) {

    e->rotation += r;

    // clamp between 0 and 2 Pi
    if (e->rotation >= TWO_PI) {
        e->rotation -= TWO_PI;
    } else if (e->rotation < 0) {
        e->rotation += TWO_PI;
    }
}
// rotates entity to specific angle
void entity_rotateTo(entity_t* e, fixP_t r) {

    e->rotation = r;
}

// updates the entity and the underlying physics object
void entity_update(entity_t* e) {

    phyO_update(&e->phyO);
    if (e->damageFrame > 0) {
        e->damageFrame--;
    }
}
// function to handle a colliding entity
void entity_colliding(entity_t* e) {

    _entity_takeDamage(e);
    e->damageFrame = 20;
}

void _entity_takeDamage(entity_t* e) {

    if (e->health > 0) {
        e->health--;
    }
    if (e->health == 0) {
        e->phyO.exists = 0;
    }
}

void entity_heal(entity_t* e) {

    if (e->health < e->maxHealth) {
        e->health++;
    }
}
