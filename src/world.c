
#include "world.h"

uint16_t _world_timeSinceClear = 0;
uint8_t _world_clearRequest = 0;

void world_init() {

    _e_textureCalc(E_TYPE_PLAYER);
    _e_textureCalc(E_TYPE_CARGO_SHIP);

    wave = 1; // TEMPORARY

    // clears all characters stored in the UART FIFO.
    uart_clear();
}

void _world_startLevel() {

    GPIO_setLed(RED);

    playerActive = 0; // TEMPORARY

    nextLevelTimer = 0; // TEMPORARY
        /*
    Everything in the world is initialized as "not existing"
    since this ensures that we don't unintentionally draw or
    check collisions for anything that we haven't deliberately
    added
    */

    int i;
    for (i = 0; i < MAX_PLAYERS; i++) {
        players[i].e.phyO.exists = 0;
    }

    for (i = 1; i < MAX_ENEMIES - 1; i++) {
        enemies[i].e.phyO.exists = 0;
    }

    for (i = 0; i < MAX_BULLETS_PLAYER; i++) {
        bullets_player[i].phyO.exists = 0;
    }

    for (i = 0; i < MAX_ASTEROIDS; i++) {
        asteroids[i].phyO.exists = 0;
    }

    for (i = 0; i < MAX_POWER_UPS; i++) {
        powerUps[i].phyO.exists = 0;
    }
}

void world_randomize(uint8_t playerOne, uint8_t playerTwo) {

    srand(time_15);

    /*
    The "world" is 256*256 characters. To eliminate wrapping around the borders
    of the world, the play area is restricted between 6 and 248 horizontally and
    vertically. To avoid spawning enemies or players etc. on the border, or out-
    side of the play area, the area is limited between 8 and 246. Each texture
    is a maximum of 8*8. This means the play area can be divided into a 29*29
    grid of 8*8 squares.
    */
    #define WORLD_GRID_SIZE 29

    #define SPAWN_CARGO_CHANCE 4

    // World grid starts in (8,8).
    fixP_t x = 8 << 14;
    fixP_t y = 8 << 14;
    // Increments by 8 in each direction.
    #define X_NEXT 8 << 14
    #define Y_NEXT 8 << 14

    // determines a random square in the grid for the players to spawn
    fixP_t player1_x = x + ((rand() % 29) * 8 << 14);
    fixP_t player1_y = y + ((rand() % 29) * 8 << 14);

    fixP_t player2_x = x + ((rand() % 29) * 8 << 14);
    fixP_t player2_y = y + ((rand() % 29) * 8 << 14);

    vec_t pos;
    vec_t vel;

    int asteroidCount = 0;
    int enemyCount = 0;

    int i, j;

    for (i = 0; i < WORLD_GRID_SIZE; i++) {

        for(j = 0; j < WORLD_GRID_SIZE; j++) {

            if ((x == player1_x && y == player1_y) || (x == player2_x && y == player2_y)) {
                continue;
            }

            // on average 75% of the world is empty
            int empty = rand() % (20 + (WORLD_GRID_SIZE * WORLD_GRID_SIZE) / (MAX_ASTEROIDS + MAX_ENEMIES)) ;

            // 0 = enemy, 1 and 2 = asteroid. enemy:asteroid ratio 1:2
            int asteroid = rand() % 3;

            /*
            ASTEROID
            0 = small
            1 = medium
            2 = large
            ENEMY
            0 = kamikaze
            1 = kamikaze?
            2 = kamikaze...
            */
            int type = rand() % 3;

            if (!empty) {

                vec_init(&pos, x, y);
                vec_init(&vel, 0, 0);

                if (!asteroid && enemyCount < MAX_ENEMIES) {

                    if (rand() % SPAWN_CARGO_CHANCE != 0) {

                        enemy_init(&enemies[enemyCount], pos, KAMIKAZE_TYPE);

                    } else {

                        enemy_init(&enemies[enemyCount], pos, CARGO_TYPE);
                    }
                    enemyCount++;

                } else if (asteroid && asteroidCount < MAX_ASTEROIDS) {

                    astrd_init(&asteroids[asteroidCount], type, pos, vel);
                    asteroidCount++;
                }
            }
            x = 8 + j * X_NEXT;
        }
        y = 8 + i * Y_NEXT;
    }

    if (playerOne) {
        vec_init(&pos, player1_x, player1_y);
        player_init(&players[0], pos, 0);
    }

    if (playerTwo) {
        vec_init(&pos, player2_x, player2_y);
        player_init(&players[1], pos, 1);
    }

    GPIO_setLed(RED);
}

void _enemies_randomize() {

    fixP_t x = 8 << 14;
    fixP_t y = 8 << 14;

    vec_t pos;
    vec_t vel;

    int enemyCount = 0;

    int i, j;

    for (i = 0; i < WORLD_GRID_SIZE; i++) {

        for(j = 0; j < WORLD_GRID_SIZE; j++) {

            // on average 75% of the world is empty
            int empty = rand() % ((WORLD_GRID_SIZE * WORLD_GRID_SIZE) / (MAX_ENEMIES)) ;

            /*
            ENEMY
            0 = kamikaze
            1 = kamikaze?
            2 = kamikaze...
            */
            int type = rand() % 3;

            if (!empty) {

                vec_init(&pos, x, y);
                vec_init(&vel, 0, 0);

                if (enemyCount < MAX_ENEMIES) {

                    //enemy_init(&enemies[enemyCount], pos, type);
                    enemy_init(&enemies[enemyCount], pos, 0);
                    enemyCount++;

                }
            }
            x = 8 + j * X_NEXT;
        }
        y = 8 + i * Y_NEXT;
    }

    nextLevelTimer = 0;

}

void world_update() {

    _world_processInputs();

    if (playerActive) { // TEMPORARY
        _world_updatePositions();
        _world_checkCollision();
        GPIO_setLed(GREEN);
    }

    if (_world_timeSinceClear > 0) {
        _world_timeSinceClear--;
    } else if (_world_clearRequest) {
        world_clearScreen();
    }

    int i;
    uint8_t enemyCount = 0;
    for(i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].e.phyO.exists) {
            enemyCount++;
        }
    }

    uint8_t playerOne = players[0].e.phyO.exists;
    uint8_t playerTwo = players[1].e.phyO.exists;

    if (!playerOne && !playerTwo) {
        // restart the game somehow...
        GPIO_setLed(RED);
    }

    // TEMPORARY ---
    if (0 == enemyCount) {
        nextLevelTimer++;
    }
    if (100 == nextLevelTimer) {
        wave++;
        if (wave % 4 == 0) {
            _world_startLevel();
            world_randomize(playerOne, playerTwo);
            clrscr();
        } else {
            _enemies_randomize();
        }
    }
    // -------------
}

void _world_processInputs() {

    int elements = 0;

    int i, j, k;
    int countt = uart_get_count();
    for(i = 0; i < countt; i++) {
        // read user inputs.
        char c = uart_get_char();

        // skip character duplicates.
        for (k = 0; k < elements; k++) {
            if (redChars[k] == c) {
                goto nextChar;
            }
        }

        // take note of character
        redChars[elements] = c;
        elements++;

        // forward input to each player.
        for(j = 0; j < MAX_PLAYERS; j++) {
            player_handleInput(&players[j], c);
        }

        // TEMPORARY ---
        if (c == 'p' && !playerActive) {
            playerActive = 1;
        }
        if (c == 'b') {
            clrscr(); // clear screen quickly
            world_clearScreen(); // queue clear screen, so asteroids get redrawn

            // scuffed-ass boss key
            while(1) {
                if (uart_get_char() == 'p') {
                    break;
                }
            }
            //playerActive = 0;
        }
        // -------------

        nextChar: continue;
    }
}


void _world_updatePositions() {

    int i, j;

    // update players
    for(i = 0; i < MAX_PLAYERS; i++) {
        player_update(&players[i]);
    }

    // update enemies
    for(i = 0; i < MAX_ENEMIES; i++) {
        enemy_update(&enemies[i]);
    }

    // update player bullets
    for(i = 0; i < MAX_BULLETS_PLAYER; i++) {

        // add gravity from asteroids
        for(j = 0; j < MAX_ASTEROIDS; j++) {

            if (bullets_player[i].phyO.exists && asteroids[j].phyO.exists) {
                phyO_applyGravity(&bullets_player[i].phyO, &asteroids[j].phyO, astrd_getGravity(&asteroids[j]));
            }
        }
        bullet_update(&bullets_player[i]);
    }

    // update enemy bullets
    for(i = 0; i < MAX_BULLETS_PLAYER; i++) {
        bullet_update(&bullets_enemies[i]);
    }

    // update asteroids
    for(i = 0; i < MAX_ASTEROIDS; i++) {
        astrd_update(&asteroids[i]);
    }

    // update power-ups
    for(i = 0; i < MAX_POWER_UPS; i++) {
        powerUp_update(&powerUps[i]);
    }
}

void _world_checkCollision() {

    int i, j;
    // bounce players on border
    for(i = 0; i < MAX_PLAYERS; i++) {
        _world_bounceOnBorder(&players[i].e.phyO);
    }

    // bounce enemies on border
    for(i = 0; i < MAX_ENEMIES; i++) {

        _world_bounceOnBorder(&enemies[i].e.phyO);

        for(j = 0; j < MAX_PLAYERS; j++) {

            if (phyO_isColliding(&enemies[i].e.phyO, &players[j].e.phyO)) {

                enemy_colliding(&enemies[i]);
                player_colliding(&players[j]);
            }
        }
    }

    // check player bullet collision
    for(i = 0; i < MAX_BULLETS_PLAYER; i++) {
        // check bullets against edge of the world
        if (BULLET_TYPE_BOUNCE == (bullets_player[i].data & 0b11)) {

            _world_bounceOnBorder(&bullets_player[i].phyO);

            if(_world_isOutside(&bullets_player[i].phyO)) {

                world_clearScreen();
            }

        } else if(_world_isOutside(&bullets_player[i].phyO)) {

            bullet_colliding(&bullets_player[i]);
        }
        // check bullet and enemy collision
        for(j = 0; j < MAX_ENEMIES; j++) {

            if ((phyO_isColliding(&bullets_player[i].phyO, &enemies[j].e.phyO) && !enemies[j].e.damageFrame)) {

                enemy_colliding(&enemies[j]);
                bullet_colliding(&bullets_player[i]);
                if (bullets_player[j].data & 1 << 2) {
                    players[1].score += 5;
                } else {
                    players[0].score += 5;
                }
            }
        }
    }

    // check asteroid collision with everything else
    for (i = 0; i < MAX_ASTEROIDS; i++) {

        if (_world_isOutside(&asteroids[i].phyO)) {
            asteroids[i].phyO.exists = 0;
            world_clearScreen();
        }
        /*
        for(j = 0; j < MAX_ASTEROIDS; j++) {

            if (phyO_isColliding(&asteroids[i].phyO, &asteroids[j].phyO) && j != i) {

                astrd_colliding(&asteroids[i], asteroids[j].phyO.vel);
                astrd_colliding(&asteroids[j], asteroids[i].phyO.vel);
            }
        }
        */
        for(j = 0; j < MAX_PLAYERS; j++) {

            if (phyO_isColliding(&asteroids[i].phyO, &players[j].e.phyO) && !players[j].e.damageFrame) {

                player_colliding(&players[j]);
                astrd_colliding(&asteroids[i], players[j].e.phyO.vel);
            }
        }

        for(j = 0; j < MAX_ENEMIES; j++) {

            if ((phyO_isColliding(&asteroids[i].phyO, &enemies[j].e.phyO)) && !enemies[j].e.damageFrame)  {

                enemy_colliding(&enemies[j]);
                astrd_colliding(&asteroids[i], enemies[j].e.phyO.vel);
            }
        }

        for(j = 0; j < MAX_BULLETS_PLAYER; j++) {

            if (phyO_isColliding(&asteroids[i].phyO, &bullets_player[j].phyO)) {

                bullet_colliding(&bullets_player[j]);
            }
        }
        /*
        for(j = 0; j < MAX_BULLETS_ENEMIES; j++) {

            if (phyO_isColliding(&asteroids[i].phyO, &bullets_enemies[j].phyO)) {

                bullet_colliding(&bullets_enemies[j]);
            }
        }*/
    }
    // check power-up and player collision
    for (i = 0; i < MAX_POWER_UPS; i++) {

        _world_bounceOnBorder(&powerUps[i].phyO);

        for (j = 0; j < MAX_PLAYERS; j++) {

            if (phyO_isColliding(&powerUps[i].phyO, &players[j].e.phyO)) {

                powerUp_apply(&powerUps[i], &players[j].e);
                world_clearScreen();
            }
        }
    }
}

void world_draw() {

    int i;

    // draw players
    for(i = 0; i < MAX_PLAYERS; i++) {
        player_draw(&players[i]);
    }

    // draw enemies
    for(i = 0; i < MAX_ENEMIES; i++) {
        enemy_draw(&enemies[i]);
    }

    // draw player bullets
    fgcolor(11);
    for (i = 0; i < MAX_BULLETS_PLAYER; i++) {
        bullet_draw(&bullets_player[i]);
    }

    // draw enemy bullets
    fgcolor(11);
    for (i = 0; i < MAX_BULLETS_ENEMIES; i++) {
        bullet_draw(&bullets_enemies[i]);
    }

    // draw asteroids
    fgcolor(7);
    for (i = 0; i < MAX_ASTEROIDS; i++) {
        astrd_draw(&asteroids[i]);
    }

    // draw power-ups
    fgcolor(12);
    for (i = 0; i < MAX_POWER_UPS; i++) {
        powerUp_draw(&powerUps[i]);
    }
}

void world_clearScreen() {

    // if we haven't cleared recently
    if (0 == _world_timeSinceClear) {
        _world_timeSinceClear = WAIT_AFTER_CLEAR;
        clrscr();
        _world_clearRequest = 0;
    } else {
        _world_clearRequest = 1;
    }

    int i;
    for(i = 0; i < MAX_ASTEROIDS; i++) {
        asteroids[i].phyO.drawn = 0;
    }

    for(i = 0; i < MAX_POWER_UPS; i++) {
        powerUps[i].phyO.drawn = 0;
    }
}

void world_addBulletPlayer(uint8_t type, uint8_t playerNum, vec_t pos, fixP_t angle) {

    int i;
    for (i = 0; i < MAX_BULLETS_PLAYER; i++) {
        if (0 == bullets_player[i].phyO.exists) {
            bullet_init(&bullets_player[i], type, playerNum, pos, angle);
            return;
        }
    }
}

/*
void world_addBulletEnemy(uint8_t type, vec_t pos, fixP_t angle) {

}
*/

void world_addAsteroid(uint8_t type, vec_t pos, vec_t vel) {

    int i;
    for (i = 0; i < MAX_ASTEROIDS; i++) {
        if (0 == asteroids[i].phyO.exists) {
            astrd_init(&asteroids[i], type, pos, vel);
            return;
        }
    }
}

void world_addPowerUp(phyO_t* phyO) {

    int i;
    for (i = 0; i < MAX_POWER_UPS; i++) {
        if (0 == powerUps[i].phyO.exists) {
            powerUp_initRand(&powerUps[i], phyO);
            return;
        }
    }
}

int _world_isOutside(phyO_t* phyO) {

    return (phyO->exists && (phyO->pos.x >= WORLD_MAX || phyO->pos.x <= WORLD_MIN || phyO->pos.y <= WORLD_MIN || phyO->pos.y >= WORLD_MAX));
}


void _world_bounceOnBorder(phyO_t* phyO) {

    #define VEL_CORRECTION (1 << 11)

    if (phyO->pos.x >= WORLD_MAX) {

        phyO->vel.x = -phyO->vel.x - VEL_CORRECTION;

    } else if (phyO->pos.x <= WORLD_MIN) {

        phyO->vel.x = -phyO->vel.x + VEL_CORRECTION;
    }

    if (phyO->pos.y <= WORLD_MIN) {

        phyO->vel.y = -phyO->vel.y + VEL_CORRECTION;

    } else if (phyO->pos.y >= WORLD_MAX) {

        phyO->vel.y = -phyO->vel.y - VEL_CORRECTION;
    }
}


