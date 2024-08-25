/*
    The math library is used for fixed point calculations.
    It contains the definition for fixed point, as-well as vector and vector functions.
*/

#ifndef _MATH_H_
#define _MATH_H_

// includes
#include <stdint.h>
#include <stdio.h>

// correction for 18.14 fixed point multiplication and division.
#define FIX14_MULT(a, b) ( ((a >> 6) * (b >> 6)) >> 2 )
#define FIX14_DIV(a, b)  ( ((a) << 14) / b << 0)

// definition of min and max macros.
#define max(a, b) ((a) < (b) ? (b) : (a))
#define min(a, b) ((a) < (b) ? (a) : (b))

// fixP_t is just an int32_t, but it is written wherever fixed points are used, as it clarifies the code.
#define fixP_t int32_t

// mathematical constants
#define PI 0xC90F

typedef struct {
    fixP_t x;
    fixP_t y;
} vec_t;

/* Vecot functions */
// initialize vector with given coordinates.
void vec_init(vec_t* v, fixP_t x, fixP_t y);
// rotate the vector by given 512 steps of a circle
void vec_rotate(vec_t* v, int32_t step512);
// add v2 to v1 (v1 is unchanged)
void vec_addToVec(vec_t* v1, vec_t* v2);
// multiply v by i
void vec_mulScalar(vec_t* v, fixP_t i);
// divide vector by fp
void vec_divScalar(vec_t* v, fixP_t fp);

// reduce largest coordinate to a size of one, and keep relation between x and y. (not a real unit vector, but close)
void vec_toUnitVec(vec_t* v);

// return the rounded fixed point number to 0 decimal digits
fixP_t roundFix(fixP_t fp);
// return numeric value of fixed point
fixP_t numericFix(fixP_t fp);
// round fix and return it as an int.
uint32_t fixToInt(fixP_t fp);

// returns a signed 18.14 fixed point format
fixP_t sine(int32_t step512);
fixP_t cosine(int32_t step512);


#endif /* _MATH_H_ */
