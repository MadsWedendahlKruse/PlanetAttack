
/*
    LCD library is responsible for writing text to the LCD screen.
*/

#ifndef _LCD_H_
#define _LCD_H_

// includes
#include <stdint.h>
#include <stdio.h>
#include "math.h"

#define COLUMNS 5
#define LCD_ROWS 8

// define lcd_ buffer globally to avoid fragmentation of memory.
uint8_t _lcd_buffer[512];

// initializes the LCD display
void lcd_start();

// writes a character to the LCD buffer.
void lcd_bWriteChar(char c, uint8_t x, uint8_t y);
// writes a string to the LCD buffer
void lcd_bWriteString(char* str, uint8_t x, uint8_t y);

// clears the LCD buffer
void lcd_bClear();
// show LCD buffer on the screen, must always be called after finishing writing to the buffer.
void lcd_bShow();

#endif /* _LCD_H_ */
