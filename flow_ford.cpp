#include <bits/stdc++.h>
#define pb emplace_back
#define mp make_pair

using namespace std;

//Ford Fulkerson dfs
int dfs(std::vector<std::vector<int> >& graph, std::vector<int>& par, int n, int u, int p, int t) {
	if (t == u)
		return 1000000000;
	par[u] = p;
	int fl = 0;
	for (int v = 0; v < n; ++v)
		if (par[v] = -1 && graph[u][v] > 0 && (fl = min(dfs(graph, par, n, v, u, t), graph[u][v])) > 0)
			return fl;
	return fl;
}

int bfs(std::vector<std::vector<int> >& graph, std::vector<int>& par, int n, int s, int p, int t) {
	queue<int> q;
	int fl = 0;
	q.push(s);
	parent[s] = s;
	std::vector<int> mflow(n, 0);
	mflow[s] = 1000000000;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int v = 0; v < n; v++)
			if (par[v] == -1 && graph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				mflow[v] = min(mflow[u], graph[u][v]);
			}
	}
	return mflow[t];
}
int max_flow(std::vector<std::vector<int> > graph, int n, int s, int t)
{
	int mf = 0, fl;
	std::vector<int> par(n, -1);
	while ((fl = dfs(graph, par, n, s, s, t))) { // bfs
		mf += fl;
		fill(par.begin(), par.end(), -1);
		for (int i = t; i != s ; i = par[i])
			graph[i][par[i]] += fl, graph[par[i]][i] -= fl;
	}
	return fl;
}


int32_t main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.precision(10);

}