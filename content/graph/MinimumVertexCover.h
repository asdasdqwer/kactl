/**
 * Author: Youssef Bellahcen
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
#pragma once

#include "DFSMatching.h"

vi cover(vector<vi>& G, int n, int m) {
	g.assign(n + m, {});
	rep(i,0,n) for (int e : G[i]) g[i].push_back(n + e);
	int res = matching();
	vector<bool> lfound(n, true), seen(n + m);
	rep(i,0,n) if (mat[i] >= 0) lfound[i] = false;
	vi q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (sz(q)) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for (int e : g[i]) if (!seen[e] && mat[e] >= 0)
			seen[e] = 1, q.push_back(mat[e]);
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,n,n+m) if (seen[i]) cover.push_back(i);
	assert(sz(cover) == res);
	return cover;
}