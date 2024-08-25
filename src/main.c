#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "gameLoop.h"

int main(void) {

    // establish connection to putty
    uart_init(400000);

    #define BLACK 0
    #define WHITE 15

    // set the putty colors
    color(WHITE, BLACK);
    clrscr();

    GPIO_init();
    GPIO_initLed();
    GPIO_setLed(OFF);

    gameLoop_start();

    while(1){}
}
