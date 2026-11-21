/**
 * Author: Youssef Bellahcen
 * Description: Simple bipartite matching algorithm. g[v] are the neighbours
 * of v; edges may be stored in both directions or only one way. The graph 
 * must be bipartite.
 * Time: O(VE)
 * Status: works
 */
#pragma once

vi mat, vis; vector<vi> g;
bool dfs(int v) {
	vis[v] = 1;
	for (int x : g[v]) 
		if (mat[x] < 0 || (!vis[mat[x]] && dfs(mat[x])))
			return mat[x] = v, mat[v] = x, 1;
	return 0;
}
int matching() {
	int n = sz(g), r = 0; mat.assign(n, -1);
	rep(i,0,n) if (mat[i] < 0) vis.assign(n, 0), r += dfs(i);
	return r;
}