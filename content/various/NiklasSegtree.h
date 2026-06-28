/**
 * Author: Niklas Leinert
 * License: MIT
 * Source: me
 * Description: Lazy Segment Tree
 */

#pragma once

template<class Node, class Tag> struct SegmentTree {
    int N;
    vector<Node> S;
    vector<Tag> lazy;

    void pull(int i) {
        if(i >= N/2) return;
        pull(2 * i), pull(2 * i + 1);
        S[i] = S[2 * i] + S[2 * i + 1];
    }

    void init(int _N) {
        N = 1;
        while(N < _N) N *= 2;
        S = vector<Node>(2 * N);
        lazy = vector<Tag>(2 * N);
        for(int i = 0; i < _N;i++) S[i + N] = Node();
        pull(1);
    }

    SegmentTree(int _N) { init(_N); }

    void apply(int i, Tag v, int l = 0, int r = 0) {
        S[i].apply(v, l, r);
        lazy[i].apply(v, l, r);
    }

    void push(int i, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * i, lazy[i], l, m);
        apply(2 * i + 1, lazy[i], m + 1, r);
        lazy[i] = Tag();
    }

    Node qry(int l, int r, int a, int b, int i) {
        if(l > b || r < a) return Node();
        if(l <= a && b <= r) return S[i];
        push(i, a, b);
        int m = (a + b) / 2;
        return qry(l, r, a, m, 2 * i) + qry(l, r, m + 1, b, 2 * i + 1);
    }
    Node qry(int l, int r) { return qry(l, r, 1, N, 1);}

    void rangeUpdate(int l, int r, Tag x, int a, int b, int i) {
        if(l > b|| r < a) return;
        if(l <= a && b <= r) {
            apply(i, x, a, b);
            return;
        }
        push(i, a, b);
        int m = (a + b) / 2;
        rangeUpdate(l, r, x, a, m, 2 * i);
        rangeUpdate(l, r, x, m + 1, b, 2 * i + 1);
        S[i] = S[2 * i] + S[2 * i + 1];
    }

    void rangeUpdate(int l, int r, Tag x) { rangeUpdate(l, r, x, 1, N, 1); }
    Node operator[](int a) {return qry(a, a);}
};

struct Tag {
    ll to = -1, add = 0;
    Tag(ll t, ll a) {to = t; add = a;}
    Tag() {}
    void apply(Tag t, int l = 0, int r = 0) {
        if(t.to != -1) {
            to = t.to;
            add = 0;
        }
        add += t.add;
    }
};

ostream& operator<<(ostream& os, Tag t) {return os << "(" << t.to << ", " << t.add << ")";}

struct Node {
    ll val = 0;
    Node() {}
    Node(ll v) {val = v;}
    void apply(Tag t, int l = 0, int r = 0) {
        if(t.to != -1) val = t.to * (r - l + 1);
        val += t.add * (r - l + 1);
    }
};

Node operator+(Node a, Node b) { return Node(a.val + b.val); }

ostream& operator<<(ostream& os, Node a) {return os << a.val; }
