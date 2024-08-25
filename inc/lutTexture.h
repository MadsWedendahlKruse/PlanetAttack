/*
    Lookup table for the textures.
    Also includes a function to calculate all rotations for an entity.
*/

#ifndef _LUT_TEXTURE_H_
#define _LUT_TEXTURE_H_

#include <stdint.h>

/*
ENTITIES
An entity is a dynamic unit in the game, such as a player,
which moves and rotates freely, and as such
requires many different textures.
*/
#define ENTITY 0
// Amount of entities
#define E_AMOUNT 3
#define entityID_t uint8_t
// Entity types
#define E_TYPE_PLAYER 0
#define E_TYPE_CARGO_SHIP 1
#define E_TYPE_ENEMY_KAMIKAZE 2

/*
CONSTANT TEXTURES AND CALCULATED TEXTURES
In order to draw a rotating texture, which rotates in steps
of 22.5 degrees, the following rotations are necessary:
0, 22.5, 45, 67.5 and 90 degrees.
By flipping these textures horizontally and vertically
it is possible to draw all other rotations. 0, 22.5 and 45 degrees
of rotation must be hard-coded. By flipping the axes of texture
0 and 22.5 it is possible to calculate the textures with 67.5
and 90 degrees of rotation.
*/
// Amount of *constant* textures per entity
#define E_TEX_AMOUNT_CONST 3
// Amount of *calculated* textures per entity
#define E_TEX_AMOUNT_CALC 2

// Rotation index
#define rot_t uint8_t
#define ROTATION_STEP 0x1922 // (2*Pi / 16) in fixP_t
#define TWO_PI 0x1921F // 2*Pi in fixP_t


/*
OBJECTS
An object is a static unit in the game, such as an asteroid
or a power-up, or other things which only require a single
texture.
*/

#define objectID_t uint8_t
#define OBJECT 1
// Amount of objects
#define O_AMOUNT 6

// Object types
#define O_TYPE_ASTEROID_S 0
#define O_TYPE_ASTEROID_M 1
#define O_TYPE_ASTEROID_L 2
#define O_TYPE_PWR_UP_HEART 3
#define O_TYPE_PWR_UP_BULLET_SIZE 4
#define O_TYPE_PWR_UP_BULLET_BOUNCE 5

// All Object and entity textures are 8 * 8
#define TEX_SIZE 8
#define tex_t uint8_t


// background textures
#define BACKGROUND_NUM 1 // amount of backgrounds
#define UINTS_32_PR_ROW 8 // world is 256 and 32 * 8 = 256
#define ROWS 256

// constant entity-texture array
extern const tex_t E_TEXTURES[E_AMOUNT][E_TEX_AMOUNT_CONST][TEX_SIZE];
// calculated entity-texture array
extern tex_t e_textures[E_AMOUNT][E_TEX_AMOUNT_CALC][TEX_SIZE];

// constant object-texture array
extern const tex_t O_TEXTURES[O_AMOUNT][TEX_SIZE];

// calculate all rotations for an entity
void _e_textureCalc(uint8_t e_type);

#endif /* _LUT_TEXTURE_H_ */
