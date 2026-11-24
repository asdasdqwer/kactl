/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-24
 * License: CC0
 * Description: Convex hull with point insertions and point-in-hull queries
 *  (the boundary counts as inside). \texttt{Upper} keeps the upper hull sorted by $x$;
 *  the lower hull is the upper hull of the points $(x, -y)$.
 *  Collinear points are removed. Coordinates up to about $10^9$.
 * Time: amortized O(\log N) per operation
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;
struct Upper : set<P> {
	bool bad(P a, P b, P c) { return (b - a).cross(c - a) >= 0; }
	bool below(P p) { // p on or below the upper hull
		auto it = lower_bound(P(p.x, LLONG_MIN));
		if (it == end()) return 0;
		if (it->x == p.x) return p.y <= it->y;
		return it != begin() && bad(*prev(it), p, *it);
	}
	void add(P p) {
		if (below(p)) return;
		auto it = lower_bound(P(p.x, LLONG_MIN));
		if (it != end() && it->x == p.x) it = erase(it);
		it = insert(it, p);
		while (next(it) != end() && next(it, 2) != end()
				&& bad(p, *next(it), *next(it, 2))) erase(next(it));
		while (it != begin() && prev(it) != begin()
				&& bad(*prev(it, 2), *prev(it), p)) erase(prev(it));
	}
};
struct DynamicHull {
	Upper up, lo;
	void add(P p) { up.add(p), lo.add(P(p.x, -p.y)); }
	bool inside(P p) { return up.below(p) && lo.below(P(p.x, -p.y)); }
};