#include <bits/stdc++.h>
#define pb emplace_back
#define mp make_pair

using namespace std;

//Edmond Karp:

int bfs(std::vector<std::vector<int> >& adj, std::vector<std::vector<int> >& cap, std::vector<int>& par, int s, int t)
{
	queue<pair<int, int> > q;
	q.push({s, INT_MAX});
	par[s] = -2;
	int u, flow;
	while (!q.empty()) {
		tie(u, flow) = q.front();
		for (int v : adj[u])
		{
			if (par[v] == -1 && cap[u][v])
			{
				par[v] = u;
				flow = min(flow, cap[u][v]);
				if (v == t)
					return flow;
				q.push({v, flow});
			}
		}
	}
	return 0;
}
//adj is of undirected graph
int max_flowek(std::vector<std::vector<int> > &adj, std::vector<std::vector<int> > cap, int s, int t)
{
	queue<pair<int, int> > q;
	std::vector<int> par(adj.size(), -1);
	int max_flow = 0;
	int aug_flow = 0;
	while (aug_flow = bfs(adj, cap, par, s, t))
	{
		max_flow += aug_flow;
		int curr = t;
		while (par[curr] != -2) {
			int prev = par[curr];
			cap[prev][curr] -= aug_flow;
			cap[curr][prev] += aug_flow;
			curr = par[curr];
		}
	}
	return max_flow;
}













int32_t main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.precision(10);

}