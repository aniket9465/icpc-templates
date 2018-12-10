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

struct node{
	int parent;
	int rank;
};

node arr[MAXN];
vector< pair<int, pair<int, int> > >edges;
vector<int> adj[MAXN];

void initialise(){
	for(int i=0; i<MAXN; i++){
		arr[i].parent = i;
		arr[i].rank = 0;
	}
}

int find_parent(int i){
	if(arr[i].parent!=i){
		arr[i].parent = find_parent(arr[i].parent);
	}
	return arr[i].parent;
}

void Union(int x, int y){
	int x_par = find_parent(x);
	int y_par = find_parent(y);
	if(arr[x_par].rank<arr[y_par].rank){
		arr[x_par].parent = y_par;
	}
	else if(arr[x_par].rank>arr[y_par].rank){
		arr[y_par].parent = x_par;
	}
	else{
		arr[y_par].parent = x_par;
		arr[x_par].rank++;
	}
}


int main(){
	// calculating weight of MST
	initialise();
	int x, y, z;
	edges.pb(mp(10, mp(0,1)));
	edges.pb(mp(6, mp(0,2)));
	edges.pb(mp(5, mp(0,3)));
	edges.pb(mp(15, mp(1,3)));
	edges.pb(mp(4, mp(2, 3)));
	sort(edges.begin(), edges.end());
	for(int i=0; i<edges.size(); i++){
		int x = find_parent(edges[i].S.F);
		int y = find_parent(edges[i].S.S);
		if(x!=y){
			weight+=edges[i].F;
			adj[x].pb(y);
			adj[y].pb(x);
			Union(x, y);
		}
	}
	cout<<weight<<endl;
	return 0;
}