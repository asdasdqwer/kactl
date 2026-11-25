/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data. Nodes are indices; 0 is the empty tree.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

const int MX = 1 << 21; // max #nodes
int L[MX], R[MX], val[MX], pri[MX], cnt[MX], tot;
mt19937 rnd(2);
int node(int v) { 
	val[++tot] = v, pri[tot] = (int)rnd(), cnt[tot] = 1;
	L[tot] = R[tot] = 0; return tot; 
}
void upd(int t) { cnt[t] = cnt[L[t]] + cnt[R[t]] + 1; }
template<class F> void each(int t, F f) {
	if (t) each(L[t], f), f(val[t]), each(R[t], f);
}
void split(int t, int k, int& a, int& b) { 
	// a = first k elements
	if (!t) { a = b = 0; return; }
	if (cnt[L[t]] >= k) split(L[t], k, a, L[t]), b = t; 
	// "val[t] >= k" for lower_bound(k)
	else split(R[t], k - cnt[L[t]] - 1, R[t], b), a = t;
	// and just "k"
	upd(t);
}
int merge(int a, int b) {
	if (!a || !b) return a | b;
	if (pri[a] > pri[b]) return R[a] = merge(R[a], b), upd(a), a;
	return L[b] = merge(a, L[b]), upd(b), b;
}
int ins(int t, int n, int pos) {
	int a, b; split(t, pos, a, b); 
	return merge(merge(a, n), b);
}
// Example application: move the range [l, r) to index k
void move(int& t, int l, int r, int k) {
	int a, b, c; split(t, l, a, b), split(b, r - l, b, c);
	t = k <= l ? merge(ins(a, b, k), c) : merge(a, ins(c, b, k - r));
}