/*
    A physics object contains a collision box, position and velocity.
    It is used to have moving objects that can be drawn on the screen.
*/

#ifndef _PHYSICS_OBJECT_H_
#define _PHYSICS_OBJECT_H_

// includes
#include <stdint.h>
#include <stdio.h>
#include "AABB.h"

typedef struct {

    AABB_t aabb; // the collision box
    vec_t pos; // the position of the physics object
    vec_t vel; // the velocity of the physics object
    fixP_t drag; // the drag that slowly slows the object
    uint8_t exists; // a flag thats is true if the physics object is alive
    uint8_t drawn; // used to avoid drawing the same stationary physics object multiple times.

} phyO_t;

// initializes the physics object with given collision extents, position, velocity and drag.
void phyO_init(phyO_t* phyO, fixP_t extents, vec_t pos, vec_t vel, fixP_t drag);

// moves the physics object by its velocity.
void phyO_update(phyO_t* phyO);

// draws the physics object if it needs to be drawn.
void phyO_draw(phyO_t* phyO, uint16_t phyO_ID);

// applies gravity force to the first physics object (phyO1).
void phyO_applyGravity(phyO_t* phyO1, phyO_t* phyO2, fixP_t scale);

// returns 1 if two physics objects are colliding.
int phyO_isColliding(phyO_t* phyO1, phyO_t* phyO2);

#endif /* _PHYSICS_OBJECT_H_ */
