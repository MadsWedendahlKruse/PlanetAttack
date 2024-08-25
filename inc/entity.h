/*
    Entity are physics objects but contain also a rotation and health.
    Entity is used by player and enemy.
*/


#ifndef _ENTITY_H_
#define _ENTITY_H_


#include "math.h"
#include "physicsObject.h"
#include "draw.h"

typedef struct {

    phyO_t phyO; // entity is also a physics object
    fixP_t rotation;
    uint8_t health; // current health
    uint8_t maxHealth; // the maximum health of the ship
    uint8_t powerUp; // active powerup on the entity
    uint8_t damageFrame; // damage frame keeps track of how far the entity is in the damage animation

} entity_t;

// initializes the entity with collision extents, position, velocity, air resistance, rotation and maximum health.
void entity_init(entity_t* e, fixP_t extents, vec_t pos, vec_t vel, fixP_t drag, fixP_t rotation, uint8_t maxHealth);
// draws the entity at the entities position
void entity_draw(entity_t* e, entityID_t entityType);

// rotate the entity
void entity_rotate(entity_t* e, fixP_t r); // increments entity rotation by angle
void entity_rotateTo(entity_t* e, fixP_t r); // rotates entity to specific angle

// updates the entity and the underlying physics object
void entity_update(entity_t* e);

// function to handle a colliding entity
void entity_colliding(entity_t* e);

// heal and damage entity by one.
void _entity_takeDamage(entity_t* e);
void entity_heal(entity_t* e);


#endif /* _ENTITY_H_ */
