#include <bits/stdc++.h>
#define pb emplace_back
#define cd complex<long double>
#define mp make_pair
#define MAXN 100000

using namespace std;

double dot(cd a, cd b) { return (conj(a) * b).real(); }
double f(cd a,  double x) {	return dot(a, {x, 1}); }
cd segtree[4 * MAXN];

void update(int node, int s, int e, cd l)
{
	int m = (s + e) >> 1;
	bool le = f(l, s) < f(segtree[node], s);
	bool mi = f(l, m) < f(segtree[node], m);
	if (mi) swap(l, segtree[node]);
	if (e - s == 1) return;
	if (le != mi) update(2 * node, s, m, l);
	update(2 * node + 1, m, e, l);
}

int query(int node, int s, int e, int x) {
	int m = (s + e) >> 1;
	if (e - s == 1)	return f(segtree[node], x);
	if (x < m) return min((int)(f(segtree[node], x)), query(2 * node, s, m, x));
	return min((int)(f(segtree[node], x)), query(2 * node + 1, m, e, x));
}

int32_t main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.precision(10);

}