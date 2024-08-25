/*
    Player is responsible for the player-controlled spaceship
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "entity.h"
#include "math.h"

// default player hitboxExtents
#define PLAYER_AABB_MIN 0xfffe0000 // -8 in fixP
#define PLAYER_AABB_EXTENT 0x00020000 //  8 in fixP
#define PLAYER_DRAG 0x3E66 // 0.975 in fixP_t
#define PLAYER_MAX_HEALTH 3

typedef struct {

    entity_t e; // the underlying entity
    uint8_t cooldown; // weapon cool-down
    char left; // left key bound to player
    char forward; // forward key bound to player
    char right; // right key bound to player
    char shoot; // shooting key bound to player
    uint16_t score; // the score of the player
    uint8_t playerNum; // (0 = player 1, 1 = player 2)

} player_t;

// initializes the player with position and player ID
void player_init(player_t* player, vec_t pos, uint8_t playerNum);
// draws the underlying entity.
void player_draw(player_t* player);

void player_rotate(player_t* player, fixP_t r); // increments player rotation by angle
void player_rotateTo(player_t* player, fixP_t r); // rotates player to specific angle

// updates player and underlying entity.
void player_update(player_t* player);

// process the key input, and perform according action
void player_handleInput(player_t* player, char c);

// function to handle a colliding player
void player_colliding(player_t* player);


#endif /* _PLAYER_H_ */
