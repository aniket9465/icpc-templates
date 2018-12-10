// Dijkstra

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define mp make_pair
#define F first
#define S second
#define MAXN 100005
#define INF 100000000000000001
#define PII pair<ll, int>

int edges, nodes;

ll dist[MAXN];
bool visit[MAXN];

priority_queue< PII, vector<PII>, greater<PII> > pq;
vector<PII> adj[MAXN];

void initialise(){
	for(int i=0; i<MAXN; i++){
		dist[i]=INF;
	}
}

void dijkstra(int x){
	int wt;
	memset(visit, false, sizeof(visit));
	initialise();
	dist[x]=0;
	pq.push(mp(0, x));
	while(!pq.empty()){
		PII p = pq.top();
		pq.pop();
		x = p.S;
		wt = p.F;
		if(visit[x])
			continue;
		visit[x]=true;
		for(int i=0; i<adj[x].size(); i++){
			int node = adj[x][i].S;
			int wtx = adj[x][i].F;
			if(wtx+dist[x]<dist[node]){
				dist[node] = wtx+dist[x];
				pq.push(mp(dist[node], node));
			}
		}
	}
}

int main(){
	int x, y;
	ll weight;
	cin>>nodes>>edges;
	for(int i=0; i<edges; i++){
		cin>>x>>y>>weight;
		adj[x].pb(mp(weight, y));
	}
	dijkstra(0);
	for(int i=0; i<nodes; i++){
		cout<<i<<" "<<dist[i]<<endl;
	}
	return 0;
}
