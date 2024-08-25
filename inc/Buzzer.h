/*
    Buzzer is responsible for communicating to the buzzer hardware and playing songs.
*/


#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "30010_io.h"
#include "stm32f30x_conf.h"
#include "lutSound.h"

#define PRESCALE_PWM 60

// the note, time and pointer to the melody thats currently playing.
uint16_t _buzzer_noteIdx; // the note we are one
uint8_t  _buzzer_time; // the time before next note
uint8_t* _buzzer_currentSong;

// initializes the buzzer
void buzzer_init();
// plays set frequency
void buzzer_setFreq(uint16_t freq);
// play this melody
void buzzer_play(const uint8_t* melody);



#endif /* _BUZZER_H_ */
