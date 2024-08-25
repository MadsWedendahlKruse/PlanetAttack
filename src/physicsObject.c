#include "physicsObject.h"

// initializes the physics object with given collision extents, position, velocity and drag.
void phyO_init(phyO_t* phyO, fixP_t extents, vec_t pos, vec_t vel, fixP_t drag){

    phyO->pos = pos;
    phyO->vel = vel;
    phyO->drag = drag;
    phyO->exists = 1; // by default the physics object is alive
    phyO->drawn = 0; // make sure it gets drawn.

    // initialize AABB so it appears around the center of the physics object.
    fixP_t halfExtent = extents >> 1;
    aabb_init(&phyO->aabb, pos.x - halfExtent, pos.y - halfExtent, extents, extents);
}

// moves the physics object by its velocity.
void phyO_update(phyO_t* phyO) {

    if (phyO->exists) {

        // apply drag
        vec_mulScalar(&phyO->vel, phyO->drag);

        // move physics object
        vec_addToVec(&phyO->pos, &phyO->vel);
        aabb_move(&phyO->aabb, phyO->vel);
    }
}

// returns 1 if two physics objects are colliding.
int phyO_isColliding(phyO_t* phyO1, phyO_t* phyO2){

    // if both physics objects exist
    if (phyO1->exists && phyO2->exists) {

        // check collision of underlying aabbs
        return aabb_isColliding(&phyO1->aabb, &phyO2->aabb);
    }
    return 0;
}

// applies gravity force to the first physics object (phyO1).
void phyO_applyGravity(phyO_t* phyO1, phyO_t* phyO2, fixP_t scale) {

    #define GRAVITY_CONST 2

    // get the path from phyO1 to phyO2 object
    vec_t path;
    vec_init(&path, phyO2->pos.x - phyO1->pos.x, phyO2->pos.y - phyO1->pos.y);

    // squared distance used by calculation
    int32_t distSqrd = (path.x >> 14) * (path.x >> 14) + (path.y >> 14) * (path.y >> 14);

    // avoid division by zero, and entity-fly-off
    if (distSqrd != 0) {

        // apply gravity formula
        path.x /= distSqrd;
        path.y /= distSqrd;

        vec_mulScalar(&path, scale * GRAVITY_CONST);

        vec_addToVec(&phyO1->vel, &path);
    }
}

// draws the physics object if it needs to be drawn.
void phyO_draw(phyO_t* phyO, uint16_t phyO_ID) {

    // don't draw physics objects if they are stationary and are already drawn
    if (phyO->exists && phyO->vel.x == 0 && phyO->vel.y == 0 && !phyO->drawn) {
        draw_phyOImg(phyO_ID, phyO->pos, phyO->vel);
        phyO->drawn = 1;

    // draw physics objects if they are moving
    } else if (phyO->exists && phyO->vel.x != 0 && phyO->vel.y != 0)  {
        draw_phyOImg(phyO_ID, phyO->pos, phyO->vel);
    }
}
