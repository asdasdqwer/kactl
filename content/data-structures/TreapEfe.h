/**
 * Author: Efe Demirler
 * Date: 2026-11-26
 * Source: folklore
 * Description: Treap usable as an
 * implicit sequence or a sorted
 * multiset, with lazy range reversal. 
 * Add aggregates in recalc, lazies in push.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once
mt19937 rng(2);
struct Node {
	Node *l = 0, *r = 0;
	int val, y, sz = 1; bool lazy = 0;
	Node(int val) : val(val), y(rng()) {}
	void recalc();
};
int cnt(Node* n) { return n ? n->sz : 0; }
void Node::recalc() { sz = cnt(l) + cnt(r) + 1; }
// lazy set => n is already reversed, its children not yet
void reverse(Node* n) {
	if (!n) return;
	n->lazy = !n->lazy; swap(n->l, n->r);
}
void push(Node* n) {
	if (!n->lazy) return;
	reverse(n->l);
	reverse(n->r);
	n->lazy = 0;
}
// each(t, [](int x) { cout << x << ' '; }); => print values in order
template<class F> void each(Node* n, F f) {
	if (n) { push(n); each(n->l, f); f(n->val); each(n->r, f); }
}
pair<Node*, Node*> split(Node* n, int k) { // first k elements in left
	if (!n) return {};
	push(n);
	if (cnt(n->l) >= k) {
		auto [L,R] = split(n->l, k);
		n->l = R; n->recalc(); return {L, n};
	} else {
		auto [L,R] = split(n->r,k - cnt(n->l) - 1);
		n->r = L; n->recalc(); return {n, R};
	}
}
// first = values < k, second = values >= k (in-order must be sorted)
pair<Node*, Node*> splitVal(Node* n, int k) {
	if (!n) return {};
	push(n);
	if (n->val >= k) {
		auto [L,R] = splitVal(n->l, k);
		n->l = R; n->recalc(); return {L, n};
	} else {
		auto [L,R] = splitVal(n->r, k);
		n->r = L; n->recalc(); return {n, R};
	}
}
Node* merge(Node* l, Node* r) {
	if (!l) return r; if (!r) return l;
	if (l->y > r->y) {
		push(l); l->r = merge(l->r, r);
		return l->recalc(), l;
	} else {
		push(r); r->l = merge(l, r->l);
		return r->recalc(), r;
	}
}