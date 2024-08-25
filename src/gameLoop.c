#include "gameLoop.h"

uint32_t _gameLoop_nxtTick = 0;
uint32_t _gameLoop_nxtSound = 0;

void gameLoop_start() {

    // initialize the buzzer (sound module)
    buzzer_init();
    // start timer 15 with reload value 9999 and prescale 49 resulting in timeout every 1/128 of a second.
    timer_start15(9999, 49);

    // start the GUI
    uint8_t players = GUI_init();

    #define PLAYER_ONE 1

    world_init();

    // add another player dependent on GUI options
    uint8_t playerTwo = (players > 1) ? 1 : 0;

    // generate a random level.
    world_randomize(PLAYER_ONE, playerTwo);

    while(1) {

        // is it time to play some sound?
        if (time_15 > _gameLoop_nxtSound) {
            _gameLoop_nxtSound++; // calculate the next time we should play a sound
            buzzer_update();

        // is it time to update the game
        } else if (time_15 > _gameLoop_nxtTick) {
            _gameLoop_nxtTick += 4; // calculate the next time we should update the game
            gameLoop_tick();
            gameLoop_frame();
            GUI_update();
        }
    }
}

void gameLoop_tick() {
    world_update();
}

void gameLoop_frame() {
    world_draw();
}
