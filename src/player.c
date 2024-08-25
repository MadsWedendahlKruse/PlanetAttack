
#include "player.h"
#include "world.h"

// initializes the player with position and player ID
void player_init(player_t* player, vec_t pos, uint8_t playerNum) {

    // set key-binds according to player ID.
    if (!playerNum) {
        player->forward = 'w';
        player->left = 'a';
        player->right = 'd';
        player->shoot = 'c';
    } else {
        player->forward = 'i';
        player->left = 'j';
        player->right = 'l';
        player->shoot = 'n';
    }

    // spawn with 0 cool-down
    player->cooldown = 0;

    // spawn with 0 velocity.
    const vec_t vel = {0, 0};
    entity_init(&player->e, 8 << 14, pos, vel, PLAYER_DRAG, 0, PLAYER_MAX_HEALTH);

    player->playerNum = playerNum;
}


// draws the underlying entity.
void player_draw(player_t* player) {

    entity_draw(&player->e, E_TYPE_PLAYER);
}

// increments player rotation by angle
void player_rotate(player_t* player, fixP_t r) {

    entity_rotate(&player->e, r);
}

 // rotates player to specific angle
void player_rotateTo(player_t* player, fixP_t r) {

    entity_rotateTo(&player->e, r);
}

// updates player and underlying entity.
void player_update(player_t* player) {

    // move entity
    entity_update(&player->e);

    // decrement weapon cool-down
    if (player->cooldown > 0) {
       player->cooldown--;
    }
}

// process the key input, and perform according action
void player_handleInput(player_t* player, char c) {

    #define ROTATION_ACCELERATION 0x0844
    #define ACCELERATION 0x0800

    // if forward key pressed
    if (c == player->forward) {

        // convert radian rotation to 512 step.
        int step = fixToInt(FIX14_DIV(player->e.rotation, ROTATION_STEP) * 32);

        // accelerate in rotation direction
        vec_t acceleration;
        vec_init(&acceleration, FIX14_MULT(ACCELERATION, cosine(step)), FIX14_MULT(ACCELERATION, -sine(step)));
        vec_addToVec(&player->e.phyO.vel, &acceleration);

    // if left key pressed
    } else if (c == player->left) {

        // rotate in positive-rotation direction (left)
        player_rotate(player, ROTATION_ACCELERATION);

    // if right key pressed
    } else if (c == player->right) {

        // rotate in right-rotation direction (right)
        player_rotate(player, -ROTATION_ACCELERATION);
    }

    // if shoot key pressed and not on cool-down.
    if (c == player->shoot && 0 == player->cooldown && player->e.phyO.exists) {

        #define DELTA_BULLET 0x0084 // random offset angle

        fixP_t bulletAngle = player->e.rotation;

        // add random delta angle to bullet.
        bulletAngle += (rand() % 21 - 10) * DELTA_BULLET;

        world_addBulletPlayer(player->e.powerUp, player->playerNum, player->e.phyO.pos, bulletAngle);

        // set weapon on cool-down.
        player->cooldown = 3;
    }
}

// function to handle a colliding player
void player_colliding(player_t* player) {

    // make player invincible while taking damage
    if (0 != player->e.damageFrame) {
        return;
    }

    entity_colliding(&player->e);

    // play sound when taking damage
    if (player->e.health == 0) {
        buzzer_play(MELODY_PLAYER_CRASH); // play death sound if dead
    } else {
        buzzer_play(MELODY_PLAYER_DAMAGE); // otherwise play damage sound
    }
}
