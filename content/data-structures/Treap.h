/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data: add an array and
 *  update it in upd (lazy tags: push them at the start of split/merge).
 *  Node 0 is the empty tree; a tree is given by its root index.
 * Usage: int t = 0; t = ins(t, node(x), pos);
 *  int a, b; split(t, k, a, b); t = merge(a, b);
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

const int MX = 1 << 21; // max number of nodes
// node i: children L[i], R[i], value val[i], priority pri[i],
// subtree size cnt[i]; cnt[0] = 0 (empty tree)
int L[MX], R[MX], val[MX], pri[MX], cnt[MX], tot;
mt19937 rnd(2);

int node(int v) { // new one-node tree holding v
	int t = ++tot;
	val[t] = v, pri[t] = (int)rnd(), cnt[t] = 1, L[t] = R[t] = 0;
	return t;
}
void upd(int t) { cnt[t] = cnt[L[t]] + cnt[R[t]] + 1; }

// a = first k elements of t, b = the rest
void split(int t, int k, int& a, int& b) {
	if (!t) { a = b = 0; return; }
	if (cnt[L[t]] >= k) { // cut lies in the left subtree
		split(L[t], k, a, L[t]);
		b = t;
	} else { // t and its left subtree go to a
		split(R[t], k - cnt[L[t]] - 1, R[t], b);
		a = t;
	}
	upd(t);
}
// for t sorted by value: a = values < k, b = values >= k
void splitVal(int t, int k, int& a, int& b) {
	if (!t) { a = b = 0; return; }
	if (val[t] >= k) splitVal(L[t], k, a, L[t]), b = t;
	else splitVal(R[t], k, R[t], b), a = t;
	upd(t);
}
// concatenation: all of a, then all of b
int merge(int a, int b) {
	if (!a || !b) return a | b;
	if (pri[a] > pri[b]) {
		R[a] = merge(R[a], b);
		upd(a); return a;
	}
	L[b] = merge(a, L[b]);
	upd(b); return b;
}
// insert tree n so that it starts at index pos
int ins(int t, int n, int pos) {
	int a, b;
	split(t, pos, a, b);
	return merge(merge(a, n), b);
}
template<class F> void each(int t, F f) { // f(value), in order
	if (t) each(L[t], f), f(val[t]), each(R[t], f);
}
// Example: move the range [l, r) to index k (k <= l or k >= r)
void move(int& t, int l, int r, int k) {
	int a, b, c;
	split(t, l, a, b), split(b, r - l, b, c);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}