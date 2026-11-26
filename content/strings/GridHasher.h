/**
 * Author: Niklas Leinert
 * License: MIT
 * Source: me
 * Description: Grid Hasher
 * Status: stress-tested
 */
#pragma once

#include "Hashing.h"

struct GridHash {
	vector<vector<H>> h; vector<H> pr, pc;
	GridHash(vector<string>& g) : h(sz(g) + 1, vector<H>(sz(g[0]) + 1)),
			pr(sz(g) + 1, 1), pc(sz(g[0]) + 1, 1) {
		rep(i,0,sz(g)) pr[i+1] = pr[i] * R;
		rep(j,0,sz(g[0])) pc[j+1] = pc[j] * C;
		rep(i,0,sz(g)) rep(j,0,sz(g[0]))
			h[i+1][j+1] = h[i][j+1] * R + h[i+1][j] * C - h[i][j] * R * C + g[i][j];
	}
	H get(int a, int b, int x, int y) { // rows [a, x), columns [b, y)
		return h[x][y] - h[a][y] * pr[x-a] - h[x][b] * pc[y-b] + h[a][b] * pr[x-a] * pc[y-b];
	}
};