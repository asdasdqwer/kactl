/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-25
 * License: CC0
 * Source: folklore
 * Description: Fenwick tree in any number of dimensions, with sizes given as
 *  template arguments. 1-indexed; ranges are inclusive. Declare it globally,
 *  since it is a plain array of $\prod (N_i + 1)$ values.
 * Usage: BIT<N, M> bit; bit.update(x, y, val);
 *  bit.query(x1, x2, y1, y2); // sum over [x1, x2] x [y1, y2]
 * Time: O(\prod \log N_i) per operation.
 * Status: stress-tested
 */
#pragma once

template<int... Ns> struct BIT {
	ll v = 0;
	void update(ll x) { v += x; }
	ll query() { return v; }
};
template<int N, int... Ns> struct BIT<N, Ns...> {
	BIT<Ns...> b[N + 1];
	template<class... A> void update(int p, A... a) {
		for (; p <= N; p += p & -p) b[p].update(a...);
	}
	template<class... A> ll query(int l, int r, A... a) {
		ll s = 0;
		for (; r > 0; r -= r & -r) s += b[r].query(a...);
		for (--l; l > 0; l -= l & -l) s -= b[l].query(a...);
		return s;
	}
};