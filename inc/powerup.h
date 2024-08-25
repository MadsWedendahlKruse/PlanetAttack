/*
    Powerups are physics objects. They drop on enemy kills (possibly on asteroids as well, but not really)
    If a player picks them up they apply an effect.
*/
#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "physicsObject.h"
#include "entity.h"
#include "buzzer.h"

#define POWER_UP_EXTENTS (8 << 14)
#define POWER_UP_DRAG 0x3E66

#define PWR_UP_COUNT 3

#define PWR_UP_HEART 0
#define PWR_UP_BULLET_SIZE 1
#define PWR_UP_BULLET_BOUNCE 2

typedef struct {
    phyO_t phyO; // underlying physics object
    uint8_t type;
} pwrUp_t;

// initialize a powerup with type, position and velocity
void powerUp_init(pwrUp_t* p, uint8_t type, vec_t pos, vec_t vel);
// initializes a random powerup type at the position and with the velocity of the physics object
void powerUp_initRand(pwrUp_t* p, phyO_t* phyO);

// draws the underlying physics object.
void powerUp_draw(pwrUp_t* p);
// updates the underlying physics object.
void powerUp_update(pwrUp_t* p);

// apply powerup to the entity
void powerUp_apply(pwrUp_t* p, entity_t* e);


#endif /* _POWERUP_H_ */
