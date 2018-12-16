#include <bits/stdc++.h>
using std::max;
typedef long long ll;
const int N = 410;
const int INF = 0x3f3f3f3f;
int _w;

int bmin( int &a, int b ) {
	return a = b < a ? b : a;
}
int bmax( int &a, int b ) {
	return a = b > a ? b : a;
}

int n, nl, nr, m, g[N][N];
int lef[N], rig[N];
int visl[N], visr[N];
int lx[N], ly[N], slack[N];
bool augment( int u ) {
	visl[u] = 1;
	for ( int v = 1; v <= n; ++v ) {
		if ( visr[v] ) continue;
		int slk = lx[u] + ly[v] - g[u][v];
		if ( !slk ) {
			visr[v] = 1;
			if ( !rig[v] || augment( rig[v] ) ) {
				rig[v] = u, lef[u] = v;
				return true;
			}
		} else {
			bmin( slack[v], slk );
		}
	}
	return false;
}
void solve() {
	for ( int i = 1; i <= n; ++i )
		for ( int j = 1; j <= n; ++j )
			bmax( ly[j], g[i][j] );
	for ( int i = 1; i <= n; ++i ) {
		for ( int j = 1; j <= n; ++j ) {
			visl[j] = visr[j] = 0;
			slack[j] = INF;
		}
		if ( augment(i) ) continue;
		while (1) {
			int d = INF, u;
			for ( int j = 1; j <= n; ++j )
				if ( !visr[j] )
					bmin( d, slack[j] );
			for ( int j = 1; j <= n; ++j ) {
				if ( !visr[j] ) {
					ly[j] -= d;
					slack[j] -= d;
					if ( !slack[j] ) u = j;
				}
				if ( !visl[j] ) {
					lx[j] += d;
				}
			}
			if ( !rig[u] ) break;
			visr[u] = 1, visl[rig[u]] = 1;
			u = rig[u];
			for ( int j = 1; j <= n; ++j )
				bmin( slack[j], lx[u] + ly[j] - g[u][j] );
		}
		for ( int j = 1; j <= n; ++j )
			visl[j] = visr[j] = 0;
		augment(i);
	}
}
int main() {
	std::ios::sync_with_stdio(false); std::cin.tie(NULL); std::cout.precision(10);
	std::cin >> nl >> nr >> m;
	n = max(nl, nr);
	while ( m-- ) {
		int u, v, w;
		std::cin >> u >> v >> w;
		bmax(g[u][v], w);
	}
	solve();
	ll ans = 0;
	for ( int i = 1; i <= n; ++i )
		ans += (lx[i] + ly[i]);
	std::cout << ans << "\n";
	for ( int i = 1; i <= nl; ++i )
		std::cout << (g[i][lef[i]] ? lef[i] : 0) << " ";
	return 0;
}