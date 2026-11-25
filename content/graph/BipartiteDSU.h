/**
 * Author: Youssef Bellahcen
 * Description: Union-find that also stores each vertex's colour relative to
 * its root. join(a,b) adds the edge a-b and returns false iff it closes an odd
 * cycle (the component stops being bipartite). find(x) = {root, colour of x
 * relative to root}; in the same component, a and b have the same colour iff
 * their colours are equal.
 * Time: O(\log N)
 */

#pragma once

struct BipartiteDSU {
	vi p, c;
	BipartiteDSU(int n) : p(n, -1), c(n) {}
	pii find(int x) {
		if (p[x] < 0) return {x, 0};
		auto [r, q] = find(p[x]);
		p[x] = r; return {r, c[x] ^= q};
	}
	bool join(int a, int b) {
		auto [x, ca] = find(a); auto [y, cb] = find(b);
		if (x == y) return ca != cb;
		if (p[x] > p[y]) swap(x, y);
		p[x] += p[y]; p[y] = x; c[y] = ca ^ cb ^ 1;
		return 1;
	}
};