
#include <stdint.h>
#include <stdio.h>

/*
    Ansi is used to send ansi codes to putty.
*/

// includes
#ifndef _ANSI_H_
#define _ANSI_H_


// change foreground color
void fgcolor(uint8_t foreground);
// change background color
void bgcolor(uint8_t background);
// change foreground and background color
void color(uint8_t foreground, uint8_t background);
// resets background color to the default color.
void resetbgcolor();

// clears the screen
void clrscr();
// clears the end of line
void clreol();
// turn on / off underline
void underline(uint8_t on);
// turns on / off blink
void blink(uint8_t on);

// turns on / off reverse color for text
void inverse(uint8_t on);

// set curser to (x,y) position.
// top left is 0, 0
void gotoXY(uint8_t x, uint8_t y);

// move curser n places.
void goUp(int16_t n);
void goDown(int16_t n);
void goLeft(int16_t n);
void goRight(int16_t n);


#endif /* _ANSI_H_ */
