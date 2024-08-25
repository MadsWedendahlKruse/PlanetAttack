/*
    Draw is responsible for drawing physics objects, entities and bullets. And clearing small areas of the screen.
*/


#ifndef _DRAW_H_
#define _DRAW_H_

// includes
#include "ansi.h"
#include "string.h"
#include "lutTexture.h"
#include "math.h"
#include "bullet.h"

#define WORLD_SIZE 255

// draw entity img centered on pos
void draw_entityImg(uint16_t entity_ID, uint8_t rotID, vec_t pos, vec_t vel);
// draw bullet top left corner is bullet position
void draw_bullet(vec_t pos, vec_t vel, uint8_t type);
// draw physics object img centered on pos
void draw_phyOImg(uint16_t phyO_ID, vec_t pos, vec_t vel);
// clears the space centerd on pos-
void draw_clearSquare(vec_t pos, vec_t vel, uint8_t size);

#endif /* _DRAW_H_ */
