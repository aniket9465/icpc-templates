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

// sum of elements in a range, replace int by ll if req
int tree[4*MAXN];
int lazy[4*MAXN]={0};

int arr[5] = {5,2,3,1,4};


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
	tree[index]=tree[2*index]+tree[2*index+1];
}

void range_update(int index, int l, int r, int x, int y, int val){
	if(lazy[index]!=0){
		tree[index]+=(r-l+1)*lazy[index];
		if(l!=r){
			lazy[2*index]+=lazy[index];
			lazy[2*index+1]+=lazy[index];
		}
		lazy[index]=0;
	}
	if(y<x || r<l || l>y || r<x){
		return;
	}
	if(x<=l && y>=r){
		tree[index]+=(r-l+1)*val;
		if(l!=r){
			lazy[2*index]+=val;
			lazy[2*index+1]+=val;
		}
		return;
	}
	int mid = (l+r)>>1;
	range_update(2*index, l, mid, x, y, val);
	range_update(2*index+1, mid+1, r, x, y, val);
	tree[index]=tree[2*index]+tree[2*index+1];
}


int query(int index, int x, int y, int l, int r){
	// work on lazy stored values
	if(lazy[index]!=0){
		tree[index]+=(r-l+1)*lazy[index];
		if(l!=r){
			lazy[2*index]+=lazy[index];
			lazy[2*index+1]+=lazy[index];
		}
		lazy[index]=0;
	}
	if(y<x || r<l || l>y || r<x){
		return 0;
	}
	if(x<=l && y>=r){
		return tree[index];
	}
	int mid = (l+r)>>1;
	int z1 = query(2*index, x, y, l, mid);
	int z2 = query(2*index+1, x, y, mid+1, r);
	return z1+z2;
}


int main(){
	// build segment tree
	build(1, 0, 4);
	int x=1, y=3, ans;
	// query on range (1, 3)
	ans = query(1, x, y, 0, 4);
	cout<<ans<<endl;
	// inc the elements in the range [2, 4] by 2
	range_update(1, 0, 4, 2, 4, 2);
	ans = query(1, x, y, 0, 4);
	cout<<ans<<endl;
	return 0;
}
