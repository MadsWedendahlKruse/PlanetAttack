#ifndef _GUI_H_
#define _GUI_H_

#include "GPIOsetup.h"
#include "LCD.h"
#include "buzzer.h"
#include "30010_io.h"



uint8_t GUI_init();
void GUI_draw_menu();
void GUI_draw_titlescreen();
void GUI_control();
void GUI_music();

void GUI_play ();
void GUI_instructions ();
void GUI_options();
void GUI_add_player();





#endif /*_GUI_H_*/
