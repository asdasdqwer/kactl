/**
 * Author: Youssef Bellahcen
 * Date: 2026-11-24
 * License: CC0
 * Description: Block-cut tree of an undirected graph. Nodes $0..n-1$ of \texttt{T}
 *  are the vertices, nodes $n..$ the blocks (biconnected components; a bridge
 *  is a block of 2 vertices); each vertex is joined to the blocks containing it.
 *  $v$ is an articulation point iff \texttt{sz(T[v]) >= 2}. A $u$-$v$ path must
 *  pass through exactly the cut vertices on the tree path from $u$ to $v$.
 *  Isolated vertices get no block. Multi-edges and self-loops are fine.
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

vector<vi> g, T; vi num, low, st; int Time;
void dfs(int v) {
	low[v] = num[v] = ++Time; st.push_back(v);
	for (int y : g[v]) {
		if (num[y]) { low[v] = min(low[v], num[y]); continue; }
		dfs(y); low[v] = min(low[v], low[y]);
		if (low[y] >= num[v]) {
			int b = sz(T); T.emplace_back(1, v); T[v].push_back(b);
			for (int x = -1; x != y; st.pop_back())
				x = st.back(), T[x].push_back(b), T[b].push_back(x);
		}
	}
}
void blockCut() {
	int n = sz(g); T.assign(n, {}); num.assign(n, 0); low = num; Time = 0;
	rep(i,0,n) if (!num[i]) dfs(i), st.pop_back();
}