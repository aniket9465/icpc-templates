#include <bits/stdc++.h>
using namespace std;
#define sd(x) scanf("%d", &x)
#define slld(x) scanf("%lld", &x)
#define all(x) x.begin(), x.end()
#define For(i, st, en) for(ll i=st; i<en; i++)
#define tr(x) for(auto it=x.begin(); it!=x.end(); it++)
#define pb push_back
#define ll long long
#define mp make_pair
#define F first
#define S second
#define MAXN 100005
#define PII pair<ll, int>

// dense graph

vector< pair<ll, int> > adj[MAXN];
bool marked[MAXN]={false};

priority_queue< PII, vector<PII>, greater<PII> > pq;

ll prim(int x){
	ll mincost = 0;
	pq.push(mp(0, x));
	while(!pq.empty()){
		PII p = pq.top();
		pq.pop();
		x = p.S;
		if(marked[x]==true){
			continue;
		}
		mincost+=p.F;
		marked[x]=true;
		for(int i=0; i<adj[x].size(); i++){
			int y = adj[x][i].F;
			if(!marked[y]){
				pq.push(adj[x][i]);
			}
		}
	}
	return mincost;
}

	
int main(){
	int nodes, edges, x, y;
	ll weight;
	cin>>edges;
	for(int i=0; i<edges; i++){
		cin>>x>>y>>weight;
		adj[x].pb(mp(weight, y));
		adj[y].pb(mp(weight, x));
	}
	ll mincost = prim(0);
	cout<<mincost<<endl;
	return 0;
}