
#include "LCD.h"
#include "charset.h"


// define lcd_ buffer globally to avoid fragmentation of memory.
uint8_t _lcd_buffer[512];

// initializes the LCD display
lcd_start() {

    lcd_init();
    lcd_bClear();
}

// writes a string to the LCD buffer
 void lcd_bWriteString(char* str, uint8_t x, uint8_t y) {

    // iterate all characters in the string
    int i = 0;
    while(str[i] != '\0') {

        // write each character to the buffer.
        lcd_bWriteChar(str[i], x + i * COLUMNS, y);
        i++;
    }
}

// writes a character to the LCD buffer.
void lcd_bWriteChar(char c, uint8_t x, uint8_t y) {

    // char x in [-4; 127]
    // char y in [-7; 31]

    #define LCD_WIDTH 0x80

    // convert character to a charset lookup table idx.
    char* character_lcd = character_data[c - 0x20];
    int j;

    // iterate the columns in the LUT
    for (j = 0; j < COLUMNS; j++) {

        // is character inside LCD screen coordinates?
        if (x + j < 128 && x + j >= 0) {

            // copy the data from the LUT into the buffer at the right location
            _lcd_buffer[x + j + (y / LCD_ROWS) * LCD_WIDTH] |= character_lcd[j] << (y % LCD_ROWS);
            _lcd_buffer[x + j + (y / LCD_ROWS + 1) * LCD_WIDTH] |= character_lcd[j] >> (LCD_ROWS - (y % LCD_ROWS));
        }
    }
}


// clears the LCD buffer
void lcd_bClear() {

    memset(_lcd_buffer, 0x00, 512); // Set each element of the buffer to 0x00 (all bits zero)
}

// show LCD buffer on the screen, must always be called after finishing writing to the buffer.
void lcd_bShow() {

    lcd_push_buffer(_lcd_buffer);
}
