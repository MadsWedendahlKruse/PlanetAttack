

#ifndef _WORLD_H_
#define _WORLD_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "stm32f30x_conf.h"
#include "30010_io.h" // Input/output library for this course
#include "GPIOsetup.h"

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "asteroid.h"
#include "powerUp.h"
#include "buzzer.h"

#define WORLD_MAX (248 << 14)
#define WORLD_MIN (6 << 14)

#define MAX_PLAYERS 2
#define MAX_ENEMIES 3
#define MAX_BULLETS_PLAYER 20
#define MAX_BULLETS_ENEMIES 30
#define MAX_ASTEROIDS 25
#define MAX_POWER_UPS 3

player_t players[MAX_PLAYERS];
enemy_t enemies[MAX_ENEMIES];
bullet_t bullets_player[MAX_BULLETS_PLAYER];
bullet_t bullets_enemies[MAX_BULLETS_ENEMIES];
astrd_t asteroids[MAX_ASTEROIDS];
pwrUp_t powerUps[MAX_POWER_UPS];

/* Limit clearscreen use*/
uint16_t _world_timeSinceClear;
uint8_t _world_clearRequest;
#define WAIT_AFTER_CLEAR 60

uint8_t playerActive; // TEMPORARY
uint8_t nextLevelTimer; // TEMPORARY
uint8_t wave; // TEMPORARY

// used for player input
#define BUFFER_SIZE 32
char redChars[BUFFER_SIZE];

void world_init();
void world_update();

void _world_processInputs();
void _world_updatePositions();
void _world_checkCollision();
void _world_startLevel();

int _world_isOutside(phyO_t* phyO);
void _world_bounceOnBorder(phyO_t* phyO);
void world_addPowerUp(phyO_t* phyO);

void world_draw();
void world_clearScreen();

void world_addBulletPlayer(uint8_t type, uint8_t playerNum, vec_t pos, fixP_t angle);
void world_addBulletEnemy(uint8_t type, vec_t pos, fixP_t angle);

#endif /* _WORLD_H_ */
