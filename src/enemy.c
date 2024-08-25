
#include "enemy.h"
#include "world.h"

// initialize enemy with position and enemy type
void enemy_init(enemy_t* enemy, vec_t pos, uint8_t type) {

    // spawn with 0 velocity.
    const vec_t vel = {0, 0};
    enemy->type = type;
    enemy->target = -1; // spawn with no target

    switch (type) {

        case KAMIKAZE_TYPE:
        entity_init(&enemy->e, KAMIKAZE_EXTENTS, pos, vel, KAMIKAZE_DRAG, 0, KAMIKAZE_MAX_HEALTH);
        break;

        case SHOOTER_TYPE:
        //_enemy_useAIShooter(enemy);
        break;

        case CARGO_TYPE:
        entity_init(&enemy->e, CARGO_EXTENTS, pos, vel, CARGO_DRAG, 0, CARGO_MAX_HEALTH);
        break;
    }
}

// draws the underlying entity
void enemy_draw(enemy_t* enemy) {

    entityID_t imgID;

    switch (enemy->type) {

        case KAMIKAZE_TYPE:
        imgID = E_TYPE_ENEMY_KAMIKAZE;
        break;

        case SHOOTER_TYPE:
        //_enemy_useAIShooter(enemy);
        break;

        case CARGO_TYPE:
        imgID = E_TYPE_CARGO_SHIP;
        break;
    }

    entity_draw(&enemy->e, imgID);
}

// rotates underlying entity by angle r
void enemy_rotate(enemy_t* enemy, fixP_t r){

    entity_rotate(&enemy->e, r);
}

// rotates underlying entity to r angle
void enemy_rotateTo(enemy_t* enemy, fixP_t r) {

    entity_rotateTo(&enemy->e, r);
}

// updates underlying entity
void enemy_update(enemy_t* enemy) {

    // select AI that is being used dependent on type of enemy
    switch (enemy->type) {

        case KAMIKAZE_TYPE:
        _enemy_useAIKamikaze(enemy);
        break;

        case SHOOTER_TYPE:
        //_enemy_useAIShooter(enemy);
        break;

        case CARGO_TYPE:
        _enemy_useAICargo(enemy);
        break;
    }

    entity_update(&enemy->e);
}


// AI used by kamikaze ships
void _enemy_useAIKamikaze(enemy_t* enemy) {

    // if no target, then find target
    if(enemy->target == -1) {

        #define MAX_SEARCH_ATTEMPTS 10

        // get random player
        int i;
        for (i = 0; i < MAX_SEARCH_ATTEMPTS; i++) {

            int possibleTarget = rand() % MAX_PLAYERS;

            if(players[possibleTarget].e.phyO.exists) {

                enemy->target = possibleTarget;
            }
        }
        return;

    // check if target is still alive
    } else {

        if(!players[enemy->target].e.phyO.exists) {

            // clear target if it does not exist
            enemy->target = -1;
            return;
        }
    }

    // calculate vector pointing towards player.
    vec_t path;
    vec_init(&path, players[enemy->target].e.phyO.pos.x - enemy->e.phyO.pos.x, players[enemy->target].e.phyO.pos.y - enemy->e.phyO.pos.y);

    // scales path to a unit vector
    vec_toUnitVec(&path);

    // apply random movement so it AI gets more interesting
    path.x = (rand() % 4) ? path.x : path.x * (rand() % 6);
    path.y = (rand() % 4) ? path.y : path.y * (rand() % 6);

    // apply acceleration, dependent on wave
    vec_mulScalar(&path, KAMIKAZE_ACCELERATION_INCREMENT * wave + KAMIKAZE_ACCELERATION_BASE);
    vec_addToVec(&enemy->e.phyO.vel, &path);
}

// AI used by Cargo ships
void _enemy_useAICargo(enemy_t* enemy) {

 #define TURN_CHANCE 8


    // if turning
    if (rand() % 4 == 0) {

        // left
        if (rand() % 3) {
            enemy_rotate(enemy, CARGO_ROTATION_STEP);
        // right
        } else {
            enemy_rotate(enemy, -CARGO_ROTATION_STEP);
        }
    }

    // convert radian rotation to 512 step of a circle.
    int step = fixToInt(FIX14_DIV(enemy->e.rotation, ROTATION_STEP) * 32);

    // accelerate in facing direction.
    vec_t acceleration;
    vec_init(&acceleration, FIX14_MULT(CARGO_ACCELERATION, cosine(step)), FIX14_MULT(CARGO_ACCELERATION, -sine(step)));
    vec_addToVec(&enemy->e.phyO.vel, &acceleration);
}

// function to handle a colliding enemy
void enemy_colliding(enemy_t* enemy) {

    // use underlying entity collide function
    entity_colliding(&enemy->e);
    buzzer_play(MELODY_SHOOT);

    // if enemy died from collision
    if (!enemy->e.phyO.exists) {

        // clear the pixels
        draw_clearSquare(enemy->e.phyO.pos, enemy->e.phyO.vel, 8);

        // drop power-up if cargo ship is destroyed-
        switch (enemy->type) {

            case CARGO_TYPE:
            world_addPowerUp(&enemy->e.phyO);
            break;
        }
    }
}
