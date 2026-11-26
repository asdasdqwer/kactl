/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-26
 * License: CC0
 * Description: Binary lifting LCA, plus virtual tree: given a subset S of
 * nodes, builds the minimal tree containing S and all pairwise LCAs
 * (at most $2|S|-1$ nodes), with edges compressed.
 * Returns pairs (index of parent in the result, original node);
 * the first entry is the root and points to itself.
 * Usage: LCA t(g, root); t.lca(a, b); t.compressTree(S);
 * Time: $O(N \log N)$ init, $O(|S| \log N)$ per compressTree
 * Status: stress-tested
 */
#pragma once

struct LCA {
	vector<vi> lft;
	vi tin, tout; int T = 0;

	LCA(vector<vi>& g, int root = 0) : lft(__lg(sz(g)) + 1,
			vi(sz(g))), tin(sz(g)), tout(sz(g)) {
		dfs(g, root, root);
		rep(k,1,sz(lft)) rep(v,0,sz(g))
			lft[k][v] = lft[k-1][lft[k-1][v]];
	}
	void dfs(vector<vi>& g, int v, int p) {
		tin[v] = T++;
		lft[0][v] = p;
		for (int u : g[v]) if (u != p) dfs(g, u, v);
		tout[v] = T;
	}

	bool anc(int a, int b) { // a ancestor of b (or a == b)?
		return tin[a] <= tin[b] && tout[b] <= tout[a];
	}
	int lca(int a, int b) {
		if (anc(a, b)) return a;
		for (int k = sz(lft); k--;)
			if (!anc(lft[k][a], b)) a = lft[k][a];
		return lft[0][a];
	}

	vector<pii> virtualTree(vi li) {
		auto cmp = [&](int a, int b) { return tin[a] < tin[b]; };
		// LCAs of neighbours in DFS order give all pairwise LCAs
		sort(all(li), cmp);
		int m = sz(li);
		rep(i,0,m-1) li.push_back(lca(li[i], li[i+1]));
		sort(all(li), cmp);
		li.erase(unique(all(li)), li.end());
		auto idx = [&](int v) {
			return int(lower_bound(all(li), v, cmp) - li.begin());
		};
		// parent of li[i+1] is lca(li[i], li[i+1])
		vector<pii> res = {{0, li[0]}};
		rep(i,0,sz(li)-1)
			res.push_back({idx(lca(li[i], li[i+1])), li[i+1]});
		return res;
	}
};