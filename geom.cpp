#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
const long double PI = acos(-1);
const double eps = 1e-9;
int cmp(long long a, long long b) { if (a == b) return 0; else if (a > b) return 1; return -1;}
int cmp(double a, double b) { if (abs(a - b) < eps) return 0; if ((a - b) > eps) return 1; return -1;}
template<typename T>
class point {
public:
	T x, y;
	point(T x = 0, T y = 0): x(x), y(y) {};
	void operator+=(const point &t) { this->x += t.x; this->y += t.y; }
	void operator-=(const point &t) { this->x -= t.x; this->y -= t.y; }
	void operator*=(T t) { this->x *= t; this->y *= t; }
	void operator/=(T t) { this->x /= t; this->y /= t; }
	point operator+(const point &t) const {	return move(point(this->x + t.x, this->y + t.y)); }
	point operator-(const point &t) const { return move(point(this->x - t.x, this->y - t.y)); }
	point operator*(const T &t) const { return move(point(this->x * t, this->y * t)); }
	point operator/(const T &t) const {	return move(point(this->x / t, this->y / t)); }
	long double polarAngleinpi() {
		if (this->x == (0)) return ((this->y > (0)) ? PI * (0.5) : PI * (1.5));
		if (this->y == (0) && this->x > (0)) return (0);
		if (this->y == (0)) return (PI); long double res = atan(abs(y / x));
		if (y > (0) && x > (0)) return res;	if (y > (0) && x < (0)) return (PI - res);
		if (y < (0) && x > (0)) return ((2) * PI - res); return (PI + res);
	}
	T operator*(const point &p) { return (this->x * p.x + this->y * p.y); }
	T operator^(const point &p) { return (this->x * p.y - this->y * p.x); }
	point rotate(long double sintheta, long double costheta) { return (costheta * this->x - sintheta * this->y, sintheta * this->x + costheta * this->y); }
	point rotate(long double theta) { return this->rotate(sin(theta), cos(theta)); }
	const static point counter90(const point &a) { return { -a.y, a.x }; }
	const static point clock90(const point &a) { return { a.y, -a.x }; }
	long double dist(const point &a = point()) { return sqrt((a - *this) * (a - *this)); }
	static T area(const point &a, const point &b, const point &c) { return ((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0); }
	static T dist(const point &a, const point &b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
	T distFromLine(point a, const long double& c) { return sqrt((((*this) * a + c) * ((*this) * a + c)) / (a * a)); }
	T distFromLine(point x, point y) { point p = (x + ((((*this - x) * y) / (y * y)) * y)); return sqrt((p - *this) * (p - *this)); }
	static bool clockwise(point a, point b, point c) { return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0; }
	static bool counterClockwise(point a, point b, point c) { return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0; }
	friend point operator* (T const &t, point const &p) { return move(p * t);}
};

template<typename T>
class ConvexHull {
	vector<point<T> > Hull;
	int n;
	int nextin(int i) { return (i == n - 1 ? 0 : i + 1);}
public:
	ConvexHull(vector<point<T> >& a) {
		if (a.size() <= 1) return;
		sort(a.begin(), a.end(), [](point<T> a, point<T> b) { return ((a.x < b.x) || (a.x == b.x && a.y < b.y)); });
		point<T> pa = a[0], pb = a.back(); std::vector<point<T> > upper, lower; upper.pb(pa), lower.pb(pa);
		for (int i = 1; i < (int)a.size(); ++i) {
			if (i == a.size() - 1 || point<T>::clockwise(pa, a[i], pb)) {
				while (upper.size() >= 2 && !point<T>::clockwise(upper[upper.size() - 2], upper[upper.size() - 1], a[i]))
					upper.pop_back();
				upper.pb(a[i]);
			}
			if (i == a.size() - 1 || point<T>::counterClockwise(pa, a[i], pb)) {
				while (lower.size() >= 2 && !point<T>::counterClockwise(lower[lower.size() - 2], lower[lower.size() - 1], a[i]))
					lower.pop_back();
				lower.pb(a[i]);
			}
		}
		for (int i = 0; i < (int)upper.size(); ++i) Hull.pb(upper[i]);
		for (int i = lower.size() - 2; i > 0 ; i--) Hull.pb(lower[i]);
		n = Hull.size();
	}
	std::vector<point<T>> Hullify() { return Hull; }
	vector<pair<point<T>, point<T> > > getPoints() {
		std::vector<pair<point<T>, point<T> > > res;
		int p = n - 1;
		int q = 0;
		while (cmp(point<T>::area(Hull[p], Hull[nextin(p)], Hull[nextin(q)]), point<T>::area(Hull[p], Hull[nextin(p)], Hull[q])) > 0) q = nextin(q);
		int q0 = q;
		while (q != 0) {
			p = nextin(p); res.pb({Hull[p], Hull[q]});
			while (cmp(point<T>::area(Hull[p], Hull[nextin(p)], Hull[nextin(q)]), point<T>::area(Hull[p], Hull[nextin(p)], Hull[q])) > 0) {
				q = nextin(q);
				if (p != 0 || q != q0) res.pb({Hull[p], Hull[q]});
				else return res;
			}
			if (cmp(point<T>::area(Hull[p], Hull[nextin(p)], Hull[nextin(q)]), point<T>::area(Hull[p], Hull[nextin(p)], Hull[q])) == 0) {
				if (p != q0 || q != n - 1) res.pb({Hull[p], Hull[nextin(q)]});
				else res.pb({Hull[nextin(p)], Hull[q]});
			}
		}
		return res;
	}
};
template<typename T>
class LineHull { // Min hull
	vector<point<T>> hull, vecs;
public:
	void addLine(point<T> a) { // must be in increasing order of slope
		while (!vecs.empty() && (vecs.back() * (a - hull.back())) < 0) { vecs.pop_back(); hull.pop_back(); }
		if (!hull.empty())	vecs.pb(point<T>::counter90(a - hull.back())); hull.pb(a);
	}
	T query(T x) {
		point<T> a = {x, 1};
		int i = (lower_bound(vecs.begin(), vecs.end(), a, [](point<T> a, point<T> b) { return (a ^ b > 0); }) - vecs.begin());
		return a * hull[i];
	}
	static LineHull merge(const LineHull &a, const LineHull &b) {
		LineHull c;
		int i1 = 0, i2 = 0, e1 = a.hull.size(), e2 = b.hull.size();
		while (i1 < e1 && i2 < e2) {
			if (a.hull[i1].x < b.hull[i2].x) c.addLine(a.hull[i1++]);
			else c.addLine(b.hull[i2++]);
		}
		while (i1 < e1) c.addLine(a.hull[i1++]);
		while (i2 < e2) c.addLine(b.hull[i2++]);
		return c;
	};
	vector<point<T>> Hullify() { return (hull); }
};
