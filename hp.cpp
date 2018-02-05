#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long double ft;
struct vect
{
	ft x, y;
	vect(ft x = 0, ft y = 0):x(x), y(y){}
	vect operator+(const vect &a) const
	{
		return vect(x + a.x, y + a.y);
	}
	vect operator-(const vect &a) const
	{
		return vect(x - a.x, y - a.y);
	}
	vect operator*(ft a) const
	{
		return vect(x * a, y * a);
	}
	vect operator/(ft a) const
	{
		return vect(x / a, y / a);
	}
	ft operator*(const vect &a) const
	{
		return x * a.y - y * a.x;
	}
	ft ang() const
	{
		return atan2(y, x);
	}
};
typedef vect point;
const ft eps = 1e-10;
int sgn(double a)
{
	return fabs(a) < eps ? 0 : a > 0 ? 1 : -1;
}
ft toleft(const point &a, const point &b, const point &c)
{
	return a * b + b * c + c * a;
}
struct line
{
	point a, b;
	line(){}
	line(point a, point b):a(a), b(b){}
	bool in(const point c)
	{
		return sgn(toleft(a, b, c)) >= 0;
	}
	ft ang()
	{
		return (b - a).ang();
	}
};
point intersect(const line &a, const line &b)
{
	ft n1 = (a.b - a.a) * (b.a - a.a), n2 = (a.b - a.a) * (b.b - a.a);
	point p;
	if (n1 * n2 > 0)
		p = (b.a * fabs(n2) - b.b * fabs(n1)) / (fabs(n2) - fabs(n1));
	else
		p = (b.a * fabs(n2) + b.b * fabs(n1)) / (fabs(n1) + fabs(n2));
	return p;
}
point ps[1515];
line ls[1515];
ft ang[1515];
int rk[1515];
bool cmp(int a, int b)
{
	return ang[a] < ang[b];
}
int deq[1515], l, r = -1;
double hp()
{
	int n;
	scanf("%d", &n);
	l = 0, r = -1;
	for (int i = 0; i < n; i++)
	{
		double x, y;
		scanf("%lf%lf", &x, &y);
		ps[i].x = x, ps[i].y = y;
	}
	ft t = 0;
	for (int i = 0; i < n - 1; i++)
		t += ps[i] * ps[i + 1];
	t += ps[n - 1] * ps[0];
	if (t < 0)
		reverse(ps, ps + n);
	for (int i = 0; i < n - 1; i++)
		ls[i] = line(ps[i], ps[i + 1]), rk[i] = i, ang[i] = ls[i].ang();
	ls[n - 1] = line(ps[n - 1], ps[0]), rk[n - 1] = n - 1, ang[n - 1] = ls[n - 1].ang();
	sort(rk, rk + n, cmp);
	int nw = 0;
	for (int i = 1; i < n; i++)
	{
		if (nw >= 0 && !sgn(ls[rk[i]].ang() - ls[rk[nw]].ang()))
		{
			if (ls[rk[nw]].in(ls[rk[i]].a))
				nw--;
		}
		rk[++nw] = rk[i];
	}
	n = nw + 1;
#define gl(x) ls[rk[x]]
	deq[++r] = 0, deq[++r] = 1;
	for (int i = 2; i < n; i++)
	{
		while (r > l && !gl(i).in(intersect(gl(deq[r]), gl(deq[r - 1]))))
			r--;
		while (r > l && !gl(i).in(intersect(gl(deq[l]), gl(deq[l + 1]))))
			l++;
		deq[++r] = i;
	}
	int tp = 1;
	while (tp)
	{
		tp = 0;
		while (r > l && !gl(deq[l]).in(intersect(gl(deq[r]), gl(deq[r - 1]))))
			r--, tp = 1;
		while (r > l && !gl(deq[r]).in(intersect(gl(deq[l]), gl(deq[l + 1]))))
			l++, tp = 1;
	}
	int np = 0;
	for (int i = l; i < r; i++)
		ps[np++] = intersect(gl(deq[i]), gl(deq[i + 1]));
	ps[np++] = intersect(gl(deq[l]), gl(deq[r]));
	ps[np++] = ps[0];
	ft ans = 0;
	for (int i = 0; i < np - 1; i++)
		ans += ps[i] * ps[i + 1];
	return ans / 2;
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		printf("%.2f\n", hp());
	return 0;
}
