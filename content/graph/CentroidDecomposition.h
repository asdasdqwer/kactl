/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-24
 * License: CC0
 * Description: Centroid decomposition of a forest. \texttt{par[v]} is the
 *  parent of $v$ in the centroid tree ($-1$ for roots), which has depth
 *  $O(\log N)$. A path $u$-$v$ passes through the lowest common centroid
 *  ancestor of $u$ and $v$. To process the component of each centroid
 *  \texttt{c} (vertices \texttt{u} with \texttt{!rem[u]}), add code where marked.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

struct Centroid {
	vector<vi>& g; vi s, par; vector<bool> rem;
	Centroid(vector<vi>& g) : g(g), s(sz(g)), par(sz(g), -1), rem(sz(g)) {
		rep(i,0,sz(g)) if (!rem[i]) build(i, -1);
	}
	int calc(int v, int p) {
		s[v] = 1;
		for (int u : g[v]) if (u != p && !rem[u]) s[v] += calc(u, v);
		return s[v];
	}
	void build(int c, int p) {
		int n = calc(c, -1), q = -1;
		for (bool go = 1; go;) {
			go = 0;
			for (int u : g[c]) if (u != q && !rem[u] && 2 * s[u] > n)
				{ q = c, c = u, go = 1; break; }
		}
		par[c] = p; // process component of c here, then:
		rem[c] = 1;
		for (int u : g[c]) if (!rem[u]) build(u, c);
	}
};