#include <bits/stdc++.h>
#define pb emplace_back
#define mp make_pair
#define comp Complex
#define int long long

using namespace std;

long double PI = acos(-1);

struct Complex {
	long double x, y;
	Complex(int x): x(x), y(0) {};
	Complex(long double x = (long double)(0), long double y = (long double)(0)): x(x), y(y) {};
	Complex operator+(const Complex &a) {return comp(a.x + this->x, a.y + this->y);}
	Complex operator-(const Complex &a) {return comp(this->x - a.x, this->y - a.y);}
	Complex operator*(const Complex &a) {return comp(a.x * this->x - a.y * this->y, a.x * this->y + a.y * this->x);}
	Complex operator*(const long double &a) {return comp(a * this->x, a * this->y);}
	Complex operator/(const long double &a) {return comp(this->x / a, this->y / a);}
	void operator+=(const Complex &a) {this->x += a.x; this->y += a.y;}
	void operator-=(const Complex &a) {this->x -= a.x; this->y -= a.y;}
	void operator*=(const Complex &a) {long double r = this->x; this->x = a.x * r - a.y * this->y; this->y = a.x * this->y + a.y * r; }
	void operator*=(const long double &a) { this->x *= a; this->y *= a;}
	void operator/=(const long double &a) { this->x /= a; this->y /= a;}
	Complex conj() { return comp(this->x, -this->y);}
};

void fft(std::vector<comp>& a, bool invert)
{
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		long double angle = ((invert ? -2.0l : 2.0l) * PI) / (long double)(len);
		comp wlen(cos(angle), sin(angle));
		for (int i = 0; i < n; i += len) {
			comp w(1ll);
			for (int j = 0; j < (len >> 1); ++j) {
				comp u = a[i + j], v = a[i + j + (len >> 1)] * w;
				a[i + j] = u + v;
				a[i + j + (len >> 1)] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)	for (int i = 0; i < n; ++i) a[i] /= (long double)n;
}

std::vector<int> polymul(const std::vector<int>& a, const std::vector<int>& b)
{
	int n = a.size() + b.size();
	int N = (n & (n - 1)) ? (1 << (32 - __builtin_clz(n))) : n;
	std::vector<comp> a1(a.begin(), a.end());
	std::vector<comp> b1(b.begin(), b.end());
	a1.resize(N);
	b1.resize(N);
	fft(a1, false);
	fft(b1, false);
	for (int i = 0; i < N; ++i) a1[i] *= b1[i];
	fft(a1, true);
	std::vector<int> c(n - 1);
	for (int i = 0; i < n - 1; ++i) c[i] = round(a1[i].x);
	return c;
}


int root = 5, root_1 = 4404020, MOD = 7340033, root_pw = 1 << 20;
// int root = 2187, root_1 = 410692747, MOD = 469762049, root_pw = 1 << 26;
void ntt(std::vector<int>& a, bool invert)
{
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int i = 0; i < n; ++i) a[i] = (a[i] % MOD + MOD) % MOD;
	for (int len = 2; len <= n; len <<= 1) {
		int wlen = invert ? root_1 : root;
		for (int i = len; i < root_pw; i <<= 1) wlen = (int)(1LL * wlen * wlen % MOD);
		for (int i = 0; i < n; i += len) {
			int w = 1;
			for (int j = 0; j < len / 2; j++) {
				int u = a[i + j], v = (int)(1LL * a[i + j + len / 2] * w % MOD);
				a[i + j] = u + v < MOD ? u + v : u + v - MOD;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
				w = (int)(1LL * w * wlen % MOD);
			}
		}
	}
	if (invert) {
		int n_1 = powm(n, MOD - 2, MOD);
		for (int & x : a) x = (int)(1LL * x * n_1 % MOD + MOD) % MOD;
	}
}

std::vector<int> polymulntt(const std::vector<int>& a, const std::vector<int>& b)
{
	int n = a.size() + b.size();
	int N = (n & (n - 1)) ? (1 << (32 - __builtin_clz(n))) : n;
	std::vector<int> a1(a.begin(), a.end());
	std::vector<int> b1(b.begin(), b.end());
	a1.resize(N);
	b1.resize(N);
	ntt(a1, false);
	ntt(b1, false);
	for (int i = 0; i < N; ++i) a1[i] = a1[i] * b1[i];
	ntt(a1, true);
	std::vector<int> c(n - 1);
	for (int i = 0; i < n - 1; ++i)c[i] = a1[i];
	return c;
}
