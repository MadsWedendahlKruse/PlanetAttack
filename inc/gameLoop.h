/*
    The game-loop contains the loop that is updating the game, it scedules sound, updating of objects and drawing.
*/

#ifndef _GAME_LOOP_H_
#define _GAME_LOOP_H_

// includes
#include "math.h"
#include "timer.h"
#include "world.h"
#include "GUI.h"

#define TIMER_VALUE 1

// the time, in 1/128ths of a second , when the next tick/sound should occur.
uint32_t _gameLoop_nxtTick;
uint32_t _gameLoop_nxtSound;

// starts the game loop
void gameLoop_start();

// updates all game objects
void gameLoop_tick();
// draws all game objects
void gameLoop_frame();



#endif /* _GAME_LOOP_H_ */
