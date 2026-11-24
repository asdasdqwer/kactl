/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-24
 * License: CC0
 * Source: AtCoder Library (lazy_segtree)
 * Description: Iterative segment tree with lazy propagation, about 1.5x
 *  faster than a recursive one. Default: add on range, max of range.
 *  To change: \texttt{f} must be associative with identity \texttt{unit};
 *  \texttt{app(k, v)} applies tag \texttt{v} to node \texttt{k} and
 *  combines it into \texttt{lz[k]}; \texttt{L()} must mean "no tag".
 *  Range sum: \texttt{f} = $a+b$, \texttt{unit} = 0, and in \texttt{app}
 *  use \texttt{s[k] += v * (n >> \_\_lg(k))} (length of node \texttt{k}).
 *  All values start at 0.
 * Time: O(\log N).
 * Status: stress-tested
 */
#pragma once

struct Tree {
	typedef ll T; typedef ll L; // node value, lazy tag
	int n, h = 0; vector<T> s; vector<L> lz;
	static constexpr T unit = LLONG_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	void app(int k, L v) { 
		s[k] += v; 
		if (k < n) lz[k] += v;
	}
	Tree(int N) {
		while ((1 << h) < N) h++; 
		n = 1 << h; s.assign(2 * n, 0); lz.assign(n, L());
	}
	void push(int k) { 
		if (lz[k] != L()) 
			app(2 * k, lz[k]), app(2 * k + 1, lz[k]), lz[k] = L(); 
	}
	void prop(int l, int r) {
		for (int i = h; i; i--) {
			if ((l >> i << i) != l) push(l >> i);
			if ((r >> i << i) != r) push((r - 1) >> i);
		}
	}
	void update(int l, int r, L v) { // apply v to [l, r)
		l += n, r += n; prop(l, r);
		for (int a = l, b = r; a < b; a /= 2, b /= 2) {
			if (a & 1) app(a++, v);
			if (b & 1) app(--b, v);
		}
		for (int i = 1, k; i <= h; i++) {
			if ((l >> i << i) != l) k = l >> i, s[k] = f(s[2 * k], s[2 * k + 1]);
			if ((r >> i << i) != r) k = (r - 1) >> i, s[k] = f(s[2 * k], s[2 * k + 1]);
		}
	}
	T query(int l, int r) { // f of [l, r)
		l += n, r += n; prop(l, r);
		T ra = unit, rb = unit;
		for (; l < r; l /= 2, r /= 2) {
			if (l & 1) ra = f(ra, s[l++]);
			if (r & 1) rb = f(s[--r], rb);
		}
		return f(ra, rb);
	}
};