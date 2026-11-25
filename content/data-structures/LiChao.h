/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-25
 * License: CC0
 * Source: folklore
 * Description: Li Chao tree: maximum of lines $kx+m$ at integer points
 *  $x \in [lo, hi)$. Lines can also be added on a range $[ql, qr)$ only
 *  (segments). Nodes are created on demand. For minimum, negate $k$, $m$ and the result.
 *  Works for any functions crossing pairwise at most once (e.g. $a + b\,h(x)$, $h$
 *  monotone): replace Line and the empty check.
 * Usage: LiChao t(-1e9, 1e9 + 1); t.add({k, m});
 *  t.add({k, m}, l, r); t.query(x);
 * Time: O(\log C), segments O(\log^2 C), with $C = hi - lo$
 * Status: stress-tested
 */
#pragma once

struct Line {
	ll k, m;
	ll operator()(ll x) const { return k * x + m; }
};
struct LiChao { // max over lines at x in [lo, hi)
	ll lo, hi; vector<Line> f; vector<array<int, 2>> c;
	LiChao(ll lo, ll hi) : lo(lo), hi(hi) { make(); }
	int make() {
		f.push_back({0, LLONG_MIN}), c.push_back({0, 0});
		return sz(f) - 1;
	}
	void add(Line g) { add(g, lo, hi); }
	void add(Line g, ll ql, ll qr) { // only on [ql, qr)
		add(g, ql, qr, 0, lo, hi);
	}
	void add(Line g, ll ql, ll qr, int v, ll l, ll r) {
		ll m = l + (r - l) / 2; int go = 3; // bit d: child d
		if (ql <= l && r <= qr) { // covered: keep the better
			if (f[v].m == LLONG_MIN) { f[v] = g; return; }
			bool a = g(l) > f[v](l), b = g(m) > f[v](m);
			if (b) swap(g, f[v]);
			if (r - l == 1) return;
			go = a != b ? 1 : 2; // loser wins on one side
		}
		rep(d,0,2) if (go >> d & 1) {
			ll L = d ? m : l, R = d ? r : m;
			if (qr <= L || R <= ql) continue;
			if (!c[v][d]) { int k = make(); c[v][d] = k; }
			add(g, ql, qr, c[v][d], L, R);
		}
	}
	ll query(ll x) { // LLONG_MIN if no line covers x
		ll res = LLONG_MIN, l = lo, r = hi; int v = 0;
		do {
			res = max(res, f[v](x));
			ll m = l + (r - l) / 2; int d = x >= m;
			(d ? l : r) = m, v = c[v][d];
		} while (v);
		return res;
	}
};