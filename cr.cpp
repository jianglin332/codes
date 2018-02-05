#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cctype>
using namespace std;
const double eps = 1e-9;
char buf[55000];
int g()
{
	int r = 0, m = 1;
	static char *nw = buf;
	while (*nw != '-' && !isdigit(*nw))
		nw++;
	if (*nw == '-')
		m = -1, nw++;
	while (isdigit(*nw))
		r = r * 10 + *(nw++) - '0';
	return r * m;
}
struct vect
{
	double x, y;
	vect(){}
	vect(double xx, double yy):x(xx), y(yy){}
	vect operator-() const
	{
		return vect(-x, -y);
	}
	vect operator+(const vect &a) const
	{
		return vect(x + a.x, y + a.y);
	}
	double th() const
	{
		return atan2(y, x);
	}
	double len() const
	{
		return sqrt(x * x + y * y);
	}
	vect rot(double a) const
	{
		double nw = th();
		double l = len();
		nw += a;
		return vect(l * cos(nw), l * sin(nw));
	}
	bool operator<(const vect &a) const
	{
		if (abs(x - a.x) < eps)
			return y + eps < a.y;
		return x + eps < a.x;
	}
};
typedef vect pt;
struct circle
{
	pt a;
	double r;
	circle(){}
	circle(pt aa, double rr):a(aa), r(rr){}
	circle operator+(const vect &t) const
	{
		return circle(a + t, r);
	}
	circle rot(double b) const
	{
		return circle(a.rot(b), r);
	}
}cs[1111];
struct line
{
	pt p[2];
	int type;
	line(){}
	line(const pt &a, const pt &b, int t)
	{
		p[0] = a;
		p[1] = b;
		type = t;
	}
	line rot(double a) const
	{
		return line(p[0].rot(a), p[1].rot(a), type);
	}
	line operator+(const vect &a) const
	{
		return line(p[0] + a, p[1] + a, type);
	}
	double th()
	{
		return (p[1] + -p[0]).th();
	}
}ls[1111];
bool inbetween(const pt &a, const pt &b, const pt &c)
{
	return (a.x - b.x) * (b.x - c.x) + (a.y - b.y) * (b.y - c.y) - eps > 0;
}
bool in(const line &a, pt b)
{
	if (a.type & 1)
		if (inbetween(b, a.p[0], a.p[1]))
			return 0;
	if (a.type & 2)
		if (inbetween(b, a.p[1], a.p[0]))
			return 0;
	return 1;
}
struct rtp
{
	pt a[2];
	int n;
	rtp()
	{
		n = 0;
	}
	void ins(pt b)
	{
		a[n++] = b;
	}
};
rtp llintersect(const line &a, const line &b)
{
	vect t = a.p[0];
	line aa = a + (-t);
	line bb = b + (-t);
	double th = aa.th();
	aa = aa.rot(-th);
	bb = bb.rot(-th);
	pt c = bb.p[0];
	pt d = bb.p[1];
	rtp rt;
	if (abs(d.y - c.y) < eps)
		return rt;
	pt ans((c.x * d.y - c.y * d.x) / (d.y - c.y), 0);
	ans = ans.rot(th);
	ans = ans + t;
	if (in(a, ans) && in(b, ans))
		rt.ins(ans);
	return rt;
}
rtp clintersect(const line &a, const circle &b)
{
	vect t = a.p[0];
	line aa = a + (-t);
	circle bb = b + (-t);
	double th = aa.th();
	aa = aa.rot(-th);
	bb = bb.rot(-th);
	double l = bb.a.y;
	rtp rt;
	if (abs(l) - eps > bb.r)
		return rt;
	pt ans1(bb.a.x - sqrt(bb.r * bb.r - l * l), 0);
	ans1 = ans1.rot(th);
	ans1 = ans1 + t;
	if (in(a, ans1))
		rt.ins(ans1);
	if (abs(l) + eps < bb.r)
	{
		pt ans2(bb.a.x + sqrt(bb.r * bb.r - l * l), 0);
		ans2 = ans2.rot(th);
		ans2 = ans2 + t;
		if (in(a, ans2))
			rt.ins(ans2);
	}
	return rt;
}
rtp ccintersect(const circle &a, const circle &b)
{
	vect t = a.a;
	circle aa = a + (-t);
	circle bb = b + (-t);
	line l(aa.a, bb.a, 0);
	double th = l.th();
	bb = bb.rot(-th);
	rtp rt;
	if (bb.a.x - eps > aa.r + bb.r || bb.a.x + eps < abs(aa.r - bb.r))
		return rt;
	double x = (bb.a.x * bb.a.x + aa.r * aa.r - bb.r * bb.r) / (2 * bb.a.x);
	double y = aa.r * aa.r - x * x;
	if (y + eps < 0)
		return rt;
	y = sqrt(abs(y));
	rt.ins(pt(x, y).rot(th) + t);
	if (y - eps > 0)
		rt.ins(pt(x, -y).rot(th) + t);
	return rt;
}
int nl, nc;
pt ans[1111111];
int na;
void merge(const rtp &a)
{
	for (int i = 0; i < a.n; i++)
		ans[na++] = a.a[i];
}
int main()
{
	fread(buf, 50050, 1, stdin);
	int s = g(), r = g(), l = g(), c = g();
	for (int i = 0; i < s; i++)
	{
		int x = g(), y = g(), u = g(), v = g();
		ls[nl++] = line(pt(x, y), pt(u, v), 3);
	}
	for (int i = 0; i < r; i++)
	{
		int x = g(), y = g(), u = g(), v = g();
		ls[nl++] = line(pt(x, y), pt(u, v), 1);
	}
	for (int i = 0; i < l; i++)
	{
		int x = g(), y = g(), u = g(), v = g();
		ls[nl++] = line(pt(x, y), pt(u, v), 0);
	}
	for (int i = 0; i < c; i++)
	{
		int x = g(), y = g(), r = g();
		cs[nc++] = circle(pt(x, y), r);
	}
	for (int i = 0; i < nl; i++)
		for (int j = i + 1; j < nl; j++)
			merge(llintersect(ls[i], ls[j]));
	for (int i = 0; i < nl; i++)
		for (int j = 0; j < nc; j++)
			merge(clintersect(ls[i], cs[j]));
	for (int i = 0; i < nc; i++)
		for (int j = i + 1; j < nc; j++)
			merge(ccintersect(cs[i], cs[j]));
	sort(ans, ans + na);
	pt prev(859353.9654188, 54188.85935396);
	int k = 0;
	for (int i = 0; i < na; i++)
	{
		if (abs(ans[i].x - prev.x) < eps && abs(ans[i].y - prev.y) < eps)
			continue;
		k++;
		prev = ans[i];
	}
	printf("%d", k);
	return 0;
}
