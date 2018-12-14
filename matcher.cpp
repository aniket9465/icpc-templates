#include <bits/stdc++.h>
#define pb push_back
using namespace std;
class Matcher
{
	std::vector<std::vector<int> > G;
	std::vector<int> dist, match;
	int n, m;
public:
	Matcher(int n, int m) : n(n), m(m), G(n + m + 1), match(n + m + 1), dist(n + 1) {}
	void pb(int u, int v) { G[u + 1].pb(v + 1 + n); G[v + 1 + n].pb(u + 1);}
	bool bfs() {
		int u;
		queue<int> Q;
		for (unsigned i = 1; i <= n; i++)
			if (match[i] == 0) {
				dist[i] = 0;
				Q.push(i);
			}
			else dist[i] = INT_MAX;
		dist[0] = INT_MAX;
		while (!Q.empty()) {
			u = Q.front(); Q.pop();
			if (u != 0)
				for (int v : G[u])
					if (dist[match[v]] == INT_MAX) {
						dist[match[v]] = dist[u] + 1;
						Q.push(match[v]);
					}
		}
		return (dist[0] != INT_MAX);
	}
	bool dfs(int u) {
		if (u == 0)
			return true;
		for (int v : G[u])
			if (dist[match[v]] == dist[u] + 1)
				if (dfs(match[v])) {
					match[v] = u;
					match[u] = v;
					return true;
				}
		dist[u] = INT_MAX;
		return false;
	}
	int MaxMatching() {
		int matching = 0;
		while (bfs())
			for (unsigned i = 1; i <= n; i++)
				if (match[i] == 0 && dfs(i))
					matching++;
		return matching;
	}
	std::vector<int> GetMatching() {
		std::vector<int> res(n);
		for (int i = 0; i < n; ++i)
			res[i] = match[i + 1] - n - 1;
		return res;
	}
};

int main() {
}