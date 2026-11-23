/**
 * Author: Youssef Bellahcen
 * Description: Comparator for sorting points by angle around the origin,
 * counter-clockwise starting from the positive x-axis, i.e. angle in [0, 2pi).
 * Points in the same direction compare equal. The origin is not allowed.
 * Usage: sort(all(v), polarCmp<P>);
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

template<class P> bool half(P p) { assert(p.x || p.y);
    return p.y < 0 || (p.y == 0 && p.x < 0); }
template<class P> bool polarCmp(P a, P b) {
	return half(a) != half(b) ? half(a) < half(b) : a.cross(b) > 0;
}