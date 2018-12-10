// Bellman Ford
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 5005
#define MAXE 10005
#define INF 100000000000000001

int nodect, edgect, source;

struct node{
	int src;
	int dest;
	int weight;
};

node edges[MAXE];
ll dist[MAXN];

void bellman(int stnode){
	for(int i=0; i<nodect; i++){
		if(i==source){
			dist[i]=0;
			continue;
		}
		dist[i]=INF;
	}
	for(int i=0; i<nodect; i++){
		int updates = 0;
		for(int j=0; j<edgect; j++){
			int u = edges[j].src;
			int v = edges[j].dest;
			ll weight = edges[j].weight;
			if(dist[u]!=INF && dist[u]+weight<dist[v]){
				dist[v]=dist[u]+weight;
				updates++;
			}
		}
		if(updates==0){
			break;
		}
	}
}


int main(){
	int x, y;
	ll weight;
	cin>>nodect>>edgect;
	cin>>source;
	for(int i=0; i<edgect; i++){
		cin>>x>>y>>weight;
		edges[i].src = x;
		edges[i].dest = y;
		edges[i].weight = weight;
	}
	bellman(source);
	for(int i=0; i<nodect; i++){
		cout<<i<<" "<<dist[i]<<endl;
	}
	return 0;
}
