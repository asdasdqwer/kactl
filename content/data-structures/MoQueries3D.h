/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-24
 * License: CC0
 * Description: Mo's algorithm with point updates. Query $\{l, r, t\}$ asks
 *  about $[l, r)$ after the first $t$ updates. \texttt{upd} must toggle update
 *  $t$: e.g.\ swap \texttt{a[pos]} with the stored value, and \texttt{del}/\texttt{add}
 *  \texttt{pos} around the swap if $L \le pos < R$.
 * Time: O(N^{5/3}) for $N$ = array size, \#queries, \#updates
 * Status: stress-tested
 */
#pragma once

void add(int ind, int end) { ... } // add a[ind] (end = 0 or 1)
void del(int ind, int end) { ... } // remove a[ind]
void upd(int t, int L, int R) { ... } // toggle update t
int calc() { ... } // compute current answer

vi mo3(vector<array<int, 3>> Q, int n) {
	int L = 0, R = 0, T = 0, B = max(1, (int)cbrt((double)n * n));
	vi s(sz(Q)), res = s; iota(all(s), 0);
#define K(q) tuple(q[0] / B, q[1] / B ^ -(q[0] / B & 1), q[2] ^ -(q[1] / B & 1))
	sort(all(s), [&](int a, int b) { return K(Q[a]) < K(Q[b]); });
	for (int qi : s) {
		auto [l, r, t] = Q[qi];
		while (L > l) add(--L, 0);
		while (R < r) add(R++, 1);
		while (L < l) del(L++, 0);
		while (R > r) del(--R, 1);
		while (T < t) upd(T++, L, R);
		while (T > t) upd(--T, L, R);
		res[qi] = calc();
	}
	return res;
}