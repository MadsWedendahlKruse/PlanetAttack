#include "lutTexture.h"

// constant entity-texture array
const tex_t E_TEXTURES[E_AMOUNT][E_TEX_AMOUNT_CONST][TEX_SIZE] = {
    /* PLAYER */
    // 0 degrees
    {{0x00, 0x78, 0x30, 0x7F, 0x7F, 0x30, 0x78, 0x00},
    // 22.5 degrees
    {0x00, 0x08, 0x033, 0x7F, 0x3C, 0x3A, 0x1C, 0x10},
    // 45 degrees
    {0x00, 0x26, 0x4E, 0xFC, 0x78, 0x3A, 0x1C, 0x08}},

    /* CARGO SHIP */
    // 0 degrees
    {{0x00, 0x7E, 0xFF, 0xFD, 0xFD, 0xFF, 0x7E, 0x00},
    // 22.5 degrees
    {0x0C, 0x3E, 0x0FD, 0xFD, 0xFF, 0xFF, 0x7C, 0x30},
    // 45 degrees
    {0x1E, 0x39, 0x7D, 0xFF, 0xFF, 0xFE, 0x7C, 0x38}},

    /* KAMIKAZE ENEMY */
    // 0 degrees
    {{0xFF, 0x99, 0x99, 0xE7, 0xC3, 0xC3, 0xDB, 0xFF},
    // 22.5 degrees (but really 0 degrees)
    {0xFF, 0x99, 0x99, 0xE7, 0xC3, 0xC3, 0xDB, 0xFF},
    // 45 degrees (but really 0 degrees)
    {0xFF, 0x99, 0x99, 0xE7, 0xC3, 0xC3, 0xDB, 0xFF}},
};

// calculated entity-texture array
tex_t e_textures[E_AMOUNT][E_TEX_AMOUNT_CALC][TEX_SIZE];

// constant object-texture array
const tex_t O_TEXTURES[O_AMOUNT][TEX_SIZE] = {
    // Small asteroid
    {0x00,0x00,0x18,0x3C,0x38,0x10,0x00,0x00},
    // Medium asteroid
    {0x00,0x18,0x3C,0x1E,0x3E,0x3C,0x18,0x00},
    // Large asteroid
    {0x78,0xFE,0xFF,0xFF,0x7F,0x7C,0x38,0x00},
    // Heart power-up
    {0x00, 0x6C, 0xFE, 0xFE, 0x7C, 0x38, 0x10, 0x00},
    // Bullet size power-up
    {0x00, 0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x00},
    // bullet bounce power-up
    {0x30, 0x28, 0x32, 0x29, 0xB2, 0x44, 0x28, 0x10}
};



// calculate all rotations for an entity
void _e_textureCalc(uint8_t entity) {

    memset(e_textures[entity], 0x00, E_AMOUNT * E_TEX_AMOUNT_CALC * TEX_SIZE);

    int i, col, row;


    /* Generate 90 and 67.5 rotations (in that order) */
    for(i = 0; i < E_TEX_AMOUNT_CALC; i++) {

        // iterate column index from MSB to LSB
        for (col = TEX_SIZE - 1; col >= 0; col--) {

            // bit-mask to extract column bit
            tex_t mask = 1 << col;

            for (row = 0; row < TEX_SIZE; row++) {

                e_textures[entity][i][col] |= (E_TEXTURES[entity][i][row] & mask) >> col << row;
            }
        }
    }
}

