#include "asteroid.h"

// initialize the asteroid at given size, position and velocity
void astrd_init(astrd_t* asteroid, uint8_t type, vec_t pos, vec_t vel) {

    fixP_t extents;
    fixP_t drag;

    switch(type) {

        case ASTEROID_L:
        extents = 8 << 14;
        //drag = 0x0FFF;
        drag = 0b111 << 11;
        break;

        case ASTEROID_M:
        extents = 6 << 14;
        //drag = 0x8FFF;
        drag = 0b1111 << 10;
        break;

        case ASTEROID_S:
        extents = 4 << 14;
        //drag = 0xFFFF;
        drag = 0x3F33;
        break;
    }

    phyO_init(&asteroid->phyO, extents, pos, vel, drag);
    asteroid->type = type;
}

void astrd_draw(astrd_t* asteroid){

    phyO_draw(&asteroid->phyO, asteroid->type);
}


// updates the underlying physics object.
void astrd_update(astrd_t* asteroid) {

    phyO_update(&asteroid->phyO);

}

// splits the asteroid into two smaller asteroids.
void astrd_explode(astrd_t* asteroid, vec_t impactVel){

    vec_t vel1;
    vec_t vel2;

    // calculate normal vectors of the impact-vector
    vec_init(&vel1, -impactVel.y, impactVel.x);
    vec_init(&vel2, impactVel.y, -impactVel.x);

    // create asteroids, and set their velocity along the vectors.
    world_addAsteroid(asteroid->type - 1, asteroid->phyO.pos, vel1);
    world_addAsteroid(asteroid->type - 1, asteroid->phyO.pos, vel2);

    // kill the "mother" object
    asteroid->phyO.exists = 0;
}

// logic for handling a colliding asteroid
void astrd_colliding(astrd_t* asteroid, vec_t impactVel) {

    // if asteroid is not smallest size
    if (asteroid->type != ASTEROID_S) {

        // split it in two
        astrd_explode(asteroid, impactVel);
    } else {

        // otherwise kill it
        asteroid->phyO.exists = 0;
        draw_clearSquare(asteroid->phyO.pos, 8);
    }
}

// returns the gravity strength of this asteroid
fixP_t astrd_getGravity(astrd_t* asteroid) {

    switch (asteroid->type) {

        case ASTEROID_S:
        return 0b111 << 11;

        case ASTEROID_M:
        return 0b1111 << 10;

        case ASTEROID_L:
        return 0x3F33;

    }
}
