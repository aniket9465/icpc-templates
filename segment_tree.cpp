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
#define MAXN 200005

// maxelement in a range
int tree[4*MAXN];
int arr[MAXN];


void build(int index, int l, int r){
	if(l>r){
		return;
	}
	if(l==r){
		tree[index]=arr[l];
		return;
	}
	int mid = (l+r)>>1;
	build(2*index, l, mid);
	build(2*index+1, mid+1, r);
	tree[index]=max(tree[2*index], tree[2*index+1]);
}


void update(int index, int l, int r, int pos, int val){
	if(l>r || pos>r || l>pos){
		return;
	}
	if(l==r){
		tree[index]=val;
		return;
	}
	int mid = (l+r)>>1;
	update(2*index, l, mid, pos, val);
	update(2*index+1, mid+1, r, pos, val);
	tree[index]=max(tree[2*index], tree[2*index+1]);
}

int query(int index, int x, int y, int l, int r){
	if(y<x || r<l || l>y || r<x){
		return 0;
	}
	if(x<=l && y>=r){
		return tree[index];
	}
	int mid = (l+r)>>1;
	int z1 = query(2*index, x, y, l, mid);
	int z2 = query(2*index+1, x, y, mid+1, r);
	return max(z1, z2);
}


int main(){
	// build segment tree
	build(1, 0, 4);
	int x=1, y=3, ans;
	// query on range (1, 3)
	ans = query(1, x, y, 0, 4);
	// update 3rd index by 6
	update(1, 0, 4, 3, 6);
	ans = query(1, x, y, 0, 4);
	cout<<ans<<endl;
	return 0;
}