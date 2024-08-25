/*
    Bullets are used by players and enemies to shoot other entities.
*/


#ifndef _BULLET_H_
#define _BULLET_H_

#include "physicsObject.h"
#include "draw.h"

#define BULLET_TYPE_NORMAL 0
#define BULLET_TYPE_LARGE 1
#define BULLET_TYPE_BOUNCE 2

#define BULLET_SPEED 0x0005 << 14
#define BULLET_DRAG_NORMAL 0x3F33
#define BULLET_DRAG_NONE 1 << 14

#define BULLET_SIZE_NORMAL 3
#define BULLET_SIZE_LARGE 8

typedef struct {

    phyO_t phyO; // the underlying physics object
    uint8_t data; // stores bullet type and what player spawned it
    uint16_t duration; // counter keeping track of how many ticks bullet is alive

} bullet_t;

// initializes a new bullet
void bullet_init(bullet_t* bullet, uint8_t type, uint8_t player, vec_t pos, fixP_t angle);
// updates this bullet and the underlying physics object
void bullet_update(bullet_t* bullet);
// draws the underlying physics object
void bullet_draw(bullet_t* bullet);
// function for handling a bullet that is colliding
void bullet_colliding(bullet_t* bullet);

#endif /* _BULLET_H_ */
