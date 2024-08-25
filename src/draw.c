#include "draw.h"

#define SPACE 32
#define PIXEL 219

// draw entity img centered on pos
void draw_entityImg(uint16_t entity_ID, uint8_t rotID, vec_t pos, vec_t vel) {


    // individual bits of rotID
    uint8_t a = (rotID & 0b1000) >> 3;
    uint8_t b = (rotID & 0b0100) >> 2;
    uint8_t c = (rotID & 0b0010) >> 1;
    uint8_t d = (rotID & 0b0001) >> 0;

    uint8_t idx;

    // access image on index 0 with rotID [0,4,8,12] POS = ~d*~c
    if (!d && !c) {
        idx = 0;
    // access image on index 1 with rotID [1,3,5,7,9,11,13,15] don't cares: [0,4,8,12] SOP = d
    } else if(d) {
        idx = 1;
    // access image on index 2 wit rotID [2,6,10,14]
    } else {
        idx = 2;
    }

    const tex_t* imgPtr;

    // access the hard-coded rotations on rotID [0,1,2,6,7,8,9,10,14,15] POS = (b + !c + !d)(!b + c)
    if ((b || !c || !d) && (!b || c)) {
        imgPtr = E_TEXTURES[entity_ID][idx];
    // access the calculated rotations on rotID [3,4,5,11,12,13]
    } else {
        imgPtr = e_textures[entity_ID][idx]; //use auto generated rotations.
    }


    int mirorXAdd = 0;
    int mirorXMul = 1;
    int mirorYAdd = TEX_SIZE - 1;
    int mirorYMul = -1;

    // mirror along x-axis on index [9,10,11,12,13,14,15] don't cares: [0,8] POS = a
    if(a) {
        mirorXAdd = TEX_SIZE - 1;
        mirorXMul = -1;
    }
    // mirror along y [5,6,7,8,9,10,11] don't cares: [4,12] POS = a XOR b
    if(a^b) {
        mirorYAdd = 0;
        mirorYMul = 1;
    }

    // convert x and y to integer format. Shift by half texture size, so the picture is centered in (x,y)
    pos.x = fixToInt(pos.x - (TEX_SIZE << 13));
    pos.y = fixToInt(pos.y - (TEX_SIZE << 13));

    int xMin = 0, xMax = 0, yMin = 0, yMax = 0;

    #define CLEAR_RANGE 4

    if (vel.x < 0) {
        // clear right of image
        xMax += CLEAR_RANGE;
    } else {
        // clear left of image
        xMin -= CLEAR_RANGE;
    }

    if (vel.y < 0) {
        // clear below image
        yMax += CLEAR_RANGE;

    } else {
        // clear above image
        yMin -= CLEAR_RANGE;
    }

    int i, j;
    for (i = yMin; i < TEX_SIZE + yMax; i++) {

        tex_t textureLine = 0;

        // only extract picture row if we are drawing and not clearing
        if (i >= 0 && i < TEX_SIZE) {
            textureLine = imgPtr[mirorXMul * i + mirorXAdd];
        }

        gotoXY(pos.x + xMin, pos.y + i);

        for (j = xMin; j < TEX_SIZE + xMax; j++) {

            // only extract picture column if we are drawing and not clearing
            if (j >= 0 && j < TEX_SIZE) {

                tex_t bitMask = 1 << (mirorYMul * j + mirorYAdd);

                if (bitMask & textureLine) {
                    putchar(PIXEL);
                    continue;
                }
            }
            putchar(SPACE);
        }
    }
}

void draw_bullet(vec_t pos, vec_t vel, uint8_t type) {

    int i, j;

    if (BULLET_TYPE_NORMAL == type || BULLET_TYPE_BOUNCE == type) {

        // draw bullet
        for (i = 0; i < 2; i++) {
            gotoXY(fixToInt(pos.x), fixToInt(pos.y) + i);
            for (j = 0; j < 2; j++) {
                putchar(PIXEL);
            }
        }

        // clear bullet trail
        for (i = 0; i < 2; i++) {
            gotoXY(fixToInt(pos.x - vel.x), fixToInt(pos.y - vel.y) + i);
            for (j = 0; j < 2; j++) {
                putchar(SPACE);
            }
        }

    } else if (BULLET_TYPE_LARGE == type) {

        // draw bullet
        for (i = 0; i < 4; i++) {
            gotoXY(fixToInt(pos.x), fixToInt(pos.y) + i);
            for (j = 0; j < 4; j++) {
                putchar(PIXEL);
            }
        }

        // clear bullet trail
        for (i = 0; i < 4; i++) {
            gotoXY(fixToInt(pos.x - vel.x), fixToInt(pos.y - vel.y) + i);
            for (j = 0; j < 4; j++) {
                putchar(SPACE);
            }
        }
    }
}

void draw_phyOImg(uint16_t phyO_ID, vec_t pos, vec_t vel) {

      // convert x and y to integer format. Shift by half texture size, so the picture is centered in (x,y)
    pos.x = fixToInt(pos.x - (TEX_SIZE << 13));
    pos.y = fixToInt(pos.y - (TEX_SIZE << 13));

    int xMin = 0, xMax = 0, yMin = 0, yMax = 0;

    #define CLEAR_RANGE 4

    if (vel.x < 0) {
        // clear right of image
        xMax += CLEAR_RANGE;
    } else {
        // clear left of image
        xMin -= CLEAR_RANGE;
    }

    if (vel.y < 0) {
        // clear below image
        yMax += CLEAR_RANGE;

    } else {
        // clear above image
        yMin -= CLEAR_RANGE;
    }

    int i, j;
    for (i = yMin; i < TEX_SIZE + yMax; i++) {

        tex_t textureLine = 0;

        // only extract picture row if we are drawing and not clearing
        if (i >= 0 && i < TEX_SIZE) {
            textureLine = O_TEXTURES[phyO_ID][i];
        }

        gotoXY(pos.x + xMin, pos.y + i);

        for (j = xMin; j < TEX_SIZE + xMax; j++) {

            // only extract picture column if we are drawing and not clearing
            if (j >= 0 && j < TEX_SIZE) {

                tex_t bitMask = 1 << (j);

                if (bitMask & textureLine) {
                    putchar(PIXEL);
                    continue;
                }
            }
            putchar(SPACE);
        }
    }
}



void draw_clearSquare(vec_t pos, vec_t vel, uint8_t size) {

    int i, j;
    for (i = 0; i < size; i++) {
        gotoXY(fixToInt(pos.x - vel.x) - size / 2, fixToInt(pos.y - vel.y) - size / 2 + i);
        for (j = 0; j < size; j++) {
            putchar(SPACE);
        }
    }
}
