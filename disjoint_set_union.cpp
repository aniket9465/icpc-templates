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
#define MAXN 10005

vector<int> adj[MAXN];

// find: determine the set in which the element resides
// union: merge two sets

/* 0\
   | \
   1---2
*/

struct node{
	int parent;
	int rank;
};

node arr[MAXN];

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
	if(arr[x_par].rank < arr[y_par].rank){
		arr[x_par].parent = y_par;
	}
	else if(arr[y_par].rank < arr[x_par].rank){
		arr[y_par].parent = x_par;
	}
	else{
		arr[y_par].parent = x_par;
		arr[x_par].rank++;
	}
}

bool addEdge(int a, int b){
	int x = find_parent(a);
	int y = find_parent(b);
	Union(x, y);
	return (x==y);
}


int main(){
	initialise();
	int x, y;
	bool cycle;
	x = 0; y = 1;
	cycle = addEdge(x, y);
	cout<<cycle<<endl;
	x = 1; y = 2;
	cycle = addEdge(x, y);
	cout<<cycle<<endl;
	x = 2; y = 0;
	cycle = addEdge(x, y);
	cout<<cycle<<endl;
	return 0;
}