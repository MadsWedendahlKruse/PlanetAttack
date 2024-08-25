
#include "math.h"
#include "LUTsin.h"


// initialize vector with given coordinates.
void vec_init(vec_t* v, fixP_t x, fixP_t y) {
    v->x = x;
    v->y = y;
}


// rotate the vector by given 512 steps of a circle
void vec_rotate(vec_t* v, int32_t step512) {

    // sine and cosine in 22.10 format.
    int32_t c = cosine(step512);
    int32_t s = sine(step512);

    int32_t temp_x = v->x;

    v->x = FIX14_MULT(v->x, c) - FIX14_MULT(v->y, s);
    v->y = FIX14_MULT(temp_x, s) + FIX14_MULT(v->y, c);
}

// add v2 to v1 (v1 is unchanged)
void vec_addToVec(vec_t* v1, vec_t* v2) {
    v1->x += v2->x;
    v1->y += v2->y;
}

// multiply v by i
void vec_mulScalar(vec_t* v, fixP_t i) {

    v->x = FIX14_MULT(v->x, i);
    v->y = FIX14_MULT(v->y, i);
}
// divide vector by fp
void vec_divScalar(vec_t* v, fixP_t fp) {
    v->x = FIX14_DIV(v->x, fp);
    v->y = FIX14_DIV(v->y, fp);
}

// reduce largest coordinate to a size of one, and keep relation between x and y. (not a real unit vector, but close)
void vec_toUnitVec(vec_t* v) {

    v->x = (v->x >= 0) ? 1 << 14 : -1 << 14;
    v->y = (v->y >= 0) ? 1 << 14 : -1 << 14;
}

// return the rounded fixed point number to 0 decimal digits
fixP_t roundFix(fixP_t fp) {

    #define FIRST_DECIMAL_MASK 0x2000
    #define INTEGER_MASK 0xFFFFC000
    #define ONE 0x4000

    // check if first decimal is above or below 0.5 and add 1 if above.
    return (fp & FIRST_DECIMAL_MASK) << 13 ? (fp + ONE) & INTEGER_MASK : fp & INTEGER_MASK;
}

// return numeric value of fixed point
fixP_t numericFix(fixP_t fp) {

    return fp > 0 ? fp : -fp;

}

// round fix and return it as an int.
uint32_t fixToInt(fixP_t fp) {

    return roundFix(fp) >> 14;
}


// returns a signed 18.14 fixed point format
int32_t sine(int32_t step512) {

    // only look at the 9 rightmost bits (equivalent to n %= 512)
    int32_t idx = step512 & 0x000001FF;

    if (idx < 0) {
        return -SIN[-idx];
    }

    return SIN[idx];
}

// returns a signed 18.14 fixed point format
int32_t cosine(int32_t step512) {
    sine(step512 + 128);
}
