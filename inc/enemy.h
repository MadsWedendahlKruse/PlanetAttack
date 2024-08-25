
/*
    Enemy is responsible for managing and updating the enemy struct. Enemies are ships that can be shot by the player, some of them
    attack the player.
    There are three types of enemies: Kamikaze, Cargo and Shooter.
*/

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "entity.h"

// enemy types
#define KAMIKAZE_TYPE 0
#define SHOOTER_TYPE 1
#define CARGO_TYPE 2


#define KAMIKAZE_EXTENTS 0x20000 //  8 in fixP
#define KAMIKAZE_DRAG 0x3E66
#define KAMIKAZE_MAX_HEALTH 1
#define KAMIKAZE_ACCELERATION_BASE 0x0150
#define KAMIKAZE_ACCELERATION_INCREMENT 0x00B0


#define CARGO_EXTENTS 0x30000 //  12 in fixP
#define CARGO_DRAG 0x3C66
#define CARGO_ROTATION_STEP 0x0800
#define CARGO_MAX_HEALTH 4
#define CARGO_ACCELERATION 0x0100


typedef struct {

    entity_t e; // the underlying entity
    uint8_t type; // the type of enemy (kamikaze, shooter, cargo...)
    int8_t target; // the player ID to target (type and target could be combined into one data field)

} enemy_t;

// initialize enemy with position and enemy type
void enemy_init(enemy_t* enemy, vec_t pos, uint8_t type);
// draws the underlying entity
void enemy_draw(enemy_t* enemy);

// rotates underlying entities
void enemy_rotate(enemy_t* enemy, fixP_t r); // increments enemy rotation by angle
void enemy_rotateTo(enemy_t* enemy, fixP_t r); // rotates enemy to specific angle

// updates underlying entity
void enemy_update(enemy_t* enemy);

// different enemy AI's called under enemy_update
void _enemy_useAIKamikaze(enemy_t* enemy);
void _enemy_useAIShooter(enemy_t* enemy);
void _enemy_useAICargo(enemy_t* enemy);

// function to handle a colliding enemy
void enemy_colliding(enemy_t* enemy);

#endif /* _ENEMY_H_ */
