
#ifndef _AABB_H_
#define _AABB_H_

/*
    Axis Aligned Bounding Boxes (AABBs) are responsible for collision detection.
*/

#include "math.h"


// AABBs contain a minimum point and a maximum point and span in between these two.
typedef struct {
     vec_t minP;
     vec_t maxP;
 } AABB_t;

// initialize an AABB from a (x,y) point and the extents.
void aabb_init(AABB_t* aabb, fixP_t x, fixP_t y, fixP_t ex, fixP_t ey);

// moves the AABB by the given offset
void aabb_move(AABB_t* aabb, vec_t offset_x);
// moves the AABB to a the given position
void aabb_moveTo(AABB_t* aabb, vec_t pos);

// returns 1 if AABB is intersecting with another AABB (touching the boarder doesn't count) otherwise returns false.
int aabb_isColliding(AABB_t* aabb1, AABB_t* aabb2);

#endif /* AABB.h */
