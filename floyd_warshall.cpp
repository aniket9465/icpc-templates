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
#define INF 1000000000000000001
#define MAXN 505

ll dist[MAXN][MAXN];
int nodect, edgect;

void initialise(){
	for(int i=0; i<MAXN; i++){
		for(int j=0; j<MAXN; j++){
			if(i==j){
				dist[i][j]=0;
				continue;
			}
			dist[i][j]=INF;
		}
	}
}

void floyd_warshall(){
	for(int k=0; k<nodect; k++){
		for(int i=0; i<nodect; i++){
			for(int j=0; j<nodect; j++){
				if(dist[i][k]+dist[k][j]<dist[i][j]){
					dist[i][j] = dist[i][k]+dist[k][j];
				}
			}
		}
	}
}

int main(){
	initialise();
	cin>>nodect>>edgect;
	int x, y;
	ll weight;
	for(int i=0; i<edgect; i++){
		cin>>x>>y>>weight;
		dist[x][y]=weight;
	}
	floyd_warshall();
	for(int i=0; i<nodect; i++){
		for(int j=0; j<nodect; j++){
			cout<<dist[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}