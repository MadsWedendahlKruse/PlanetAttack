#include "AABB.h"
#include "math.h"

// initialize an AABB from a (x,y) point and the extents.
void aabb_init(AABB_t* aabb, fixP_t x, fixP_t y, fixP_t ex, fixP_t ey) {

    aabb->minP.x = x;
    aabb->minP.y = y;
    aabb->maxP.x = x + ex;
    aabb->maxP.y = y + ey;

}

// moves the AABB by the given offset
void  aabb_move(AABB_t* aabb, vec_t offset) {

    vec_addToVec(&aabb->minP, &offset);
    vec_addToVec(&aabb->maxP, &offset);
}

// moves the AABB to a the given position
void aabb_moveTo(AABB_t* aabb, vec_t pos) {

    // calculate the extents of the AABB
    fixP_t diffx = aabb->maxP.x - aabb->minP.x;
    fixP_t diffy = aabb->maxP.y - aabb->minP.y;

    // move the AABB
    aabb->minP.x = pos.x;
    aabb->minP.y = pos.y;
    aabb->maxP.x = diffx + pos.x;
    aabb->maxP.y = diffy + pos.y;

}

// returns 1 if AABB is intersecting with another AABB (touching the boarder doesn't count) otherwise returns false.
int aabb_isColliding(AABB_t* aabb1, AABB_t* aabb2) {

    if( aabb1->minP.x < aabb2->maxP.x &&
        aabb1->maxP.x > aabb2->minP.x &&
        aabb1->minP.y < aabb2->maxP.y &&
        aabb1->maxP.y > aabb2->minP.y) {
        return 1;
    } else {
        return 0;
    }
}
