#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long double ft;
struct vect
{
	ft x, y;
	ft ang;
	vect(ft x = 0, ft y = 0):x(x), y(y){}
	bool operator<(const vect &a) const
	{
		return ang < a.ang;
	}
	vect operator+(const vect &a) const
	{
		return vect(x + a.x, y + a.y);
	}
	vect operator-(const vect &a) const
	{
		return vect(x - a.x, y - a.y);
	}
	ft operator*(const vect &a) const
	{
		return x * a.y - y * a.x;
	}
	vect operator*(ft a) const
	{
		return vect(a * x, a * y);
	}
}ps[111], sp[111], ep[111];
typedef vect point;
int n;
bool toleft(const point &a, const point &b, const point &c)
{
	return (b - a) * (c - b) + (c - b) * (a - c) + (a - c) * (b - a)  + 1e-9 > 0;
}
point stk[111];
int ns;
ft graham()
{
	for (int i = 1; i < n; i++)
		if (ps[i].y < ps[0].y || (ps[i].y == ps[0].y && ps[i].x < ps[0].x))
			swap(ps[i], ps[0]);
	for (int i = 1; i < n; i++)
		ps[i].ang = atan2(ps[i].y - ps[0].y, ps[i].x - ps[0].x);
	sort(ps + 1, ps + n);
	ps[n] = ps[0];
	ns = -1;
	stk[++ns] = ps[0];
	stk[++ns] = ps[1];
	for (int i = 2; i <= n; i++)
	{
		while (!toleft(stk[ns - 1], stk[ns], ps[i]))
			ns--;
		stk[++ns] = ps[i];
	}
	/*
	printf("%d\n", ns);
	for (int i = 0; i <= ns; i++)
		printf("%f %f\n", stk[i].x, stk[i].y);
	*/ft ans = 0;
	for (int i = 1; i <= ns; i++)
		ans += stk[i - 1] * stk[i];
	ans /= 2;
	return ans;
}
ft calc(ft a)
{
	for (int i = 0; i < n; i++)
		ps[i] = sp[i] + (ep[i] - sp[i]) * a;
	return graham();
}
int main()
{
	freopen("garden.in", "r", stdin);
	freopen("garden.out", "w", stdout);
	scanf("%*lf%*lf%d", &n);
	for (int i = 0; i < n; i++)
	{
		double x1, y1, x2, y2;
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
		sp[i].x = x1, sp[i].y = y1, ep[i].x = x2, ep[i].y = y2;
	}
	ft ans = 1e20;
	for (int i = 0; i < 1000; i++)
	{
		ft st = i * 1e-3, ed = (i + 1) * 1e-3;
		while (ed - st > 1e-9)
		{
			ft m1 = st + (ed - st) / 3;
			ft m2 = ed - (ed - st) / 3;
			if (calc(m1) > calc(m2))
				st = m1;
			else
				ed = m2;
		}
		ans = min(ans, calc(st));
	}
	printf("%.4f", (double)ans);
	return 0;
}
