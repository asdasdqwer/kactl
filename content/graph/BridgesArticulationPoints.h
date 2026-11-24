/**
 * Author: Youssef Bellahcen
 * Description: Finds all bridges (edges on no cycle) and articulation points
 * (vertices whose removal disconnects their component) of an undirected graph.
 * br holds the ids of the bridges; cut[v] is true iff v is an articulation point.
 * Multi-edges and self-loops are fine.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bridgesCuts();
 * Time: O(V + E)
 */
vector<vector<pii>> ed; vi num, low, br; vector<bool> cut; int Time;
void dfs(int v, int pe) {
	low[v] = num[v] = ++Time; int ch = 0;
	for (auto [y, e] : ed[v]) if (e != pe) {
		if (num[y]) { low[v] = min(low[v], num[y]); continue; }
		dfs(y, e); low[v] = min(low[v], low[y]);
		if (low[y] > num[v]) br.push_back(e);
		if (low[y] >= num[v] && (pe >= 0 || ++ch > 1)) cut[v] = 1;
	}
}
void bridgesCuts() {
	int n = sz(ed); num.assign(n, 0); low = num; cut.assign(n, 0); br.clear(); Time = 0;
	rep(i,0,n) if (!num[i]) dfs(i, -1);
}