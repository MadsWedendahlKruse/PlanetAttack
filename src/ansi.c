
#include "ansi.h"

#define ESC 0x1B

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

// clear screen
void clrscr() {
    // scrolls the screen, so the last text written on the console cant be seen.
    printf("%c[2J", ESC);
}

// clear rest of line
void clreol() {
    printf("%c[K", ESC);
}

// turns on / off underline
void underline(uint8_t on) {

    if (1 == on) {

        printf("%c[4m", ESC);

    } else {

        printf("%c[24m", ESC);
    }
}

// turns on / off blink
void blink(uint8_t on) {

    if (1 == on) {

        printf("%c[5m", ESC);

    } else {

        printf("%c[25m", ESC);
    }
}

// turns on / off reverse color for text
void inverse(uint8_t on) {

    if (1 == on) {

        printf("%c[7m", ESC);

    } else {

        printf("%c[27m", ESC);
    }
}

// set curser to (x,y) position.
// top left is 0, 0
void gotoXY(uint8_t x, uint8_t y) {

     printf("%c[%d;%dH", ESC, y + 1, x + 1);
}

// move curser n places.
void goUp(int16_t n) {
    printf("%c[%dA", ESC, n);
}

void goDown(int16_t n) {
    printf("%c[%dB", ESC, n);
}

void goLeft(int16_t n) {
    printf("%c[%dD", ESC, n);
}

void goRight(int16_t n) {
    printf("%c[%dC", ESC, n);
}
