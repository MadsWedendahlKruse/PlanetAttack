/*
    GPIOsetup is used to change the output and input state of pins.
    It also reads joystick input and changes the color of the LED.
*/


#ifndef _GPIO_SETUP_H_
#define _GPIO_SETUP_H_

// includes
#include <stdint.h>
#include <stdio.h>

#include "stm32f30x_conf.h"
#include "gameLoop.h"

// LED Color definitions for LED
#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define CYAN 5
#define MAGENTA 6
#define OFF 7

// joystick state
#define JOYSTICK_UP 1 // up only, up-right or up-left
#define JOYSTICK_DOWN 2 // down only -||-
#define JOYSTICK_LEFT 4  // left only -||-
#define JOYSTICK_RIGHT 8 // right only -||-
#define JOYSTICK_CENTER 16 // pressed down in the center

// initializes the GPIO module and should be called before calling any other GPIO function
void GPIO_init();
// initializes the LED, should be called before changing LED color
void GPIO_initLed();
// initializes the joystick, should be called before reading joystick inputs
void GPIO_initJoystick();

// changes pin state to output mode
void GPIO_setPinToOut(GPIO_TypeDef* registerSet, uint16_t pin);
// changes pin state to input mode
void GPIO_setPinToRead(GPIO_TypeDef* registerSet, uint16_t pin);

// changes the logic state of an output-mode pin
void GPIO_setPinOutVal(GPIO_TypeDef* registerSet, uint16_t pin, uint8_t val);
// reads the logic state of an input-mode pin
uint8_t GPIO_readPinVal(GPIO_TypeDef* registerSet, int16_t pin);

// changes the color of the LED
void GPIO_setLed(uint8_t color);
// returns the current state of the joystick
uint8_t GPIO_readJoystick();


#endif /* _GPIO_SETUP_H_ */
