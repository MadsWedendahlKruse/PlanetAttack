/*
    Asteroids are physics objects that are mostly stationary, but on impact they split, and cause damage.
*/


#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "physicsObject.h"
#include <stdint.h>
#include <stdio.h>

/* Asteroid sizes */
#define ASTEROID_S 0
#define ASTEROID_M 1
#define ASTEROID_L 2

// asteroid is a type of physicsObject
typedef struct {
    phyO_t phyO; // the physics Object
    uint8_t type; // the size of the asteroid
} astrd_t;

// initialize the asteroid at given size, position and velocity
void astrd_init(astrd_t* asteroid, uint8_t type, vec_t pos, vec_t vel);

void astrd_draw(astrd_t* asteroid);
// updates the underlying physics object.
void astrd_update(astrd_t* asteroid);
// splits the asteroid into two smaller asteroids.
void astrd_explode(astrd_t* asteroid, vec_t impactVel);
// logic for handling a colliding asteroid
void astrd_colliding(astrd_t* asteroid, vec_t impactVel);

// returns the gravity strength of this asteroid
fixP_t astrd_getGravity(astrd_t* asteroid);


#endif /* _ASTEROID_H_ */
