#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef double ft;
struct vect
{
	ft x, y;
	vect(ft x, ft y):x(x), y(y){}
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
	ft operator%(const vect &a) const
	{
		return x * a.x + y * a.y;
	}
	ft ln() const
	{
		return x * x + y * y;
	}
	ft len() const
	{
		return sqrt(ln());
	}
	vect r9() const
	{
		return vect(-y, x);
	}
	vect resize(ft a) const
	{
		return *this / len() * a;
	}
}inv(85935396, 54188);
typedef vect point;
struct line
{
	point a, b;
	line(const point &a, const point &b):a(a), b(b){}
};
typedef line tpt;
bool inl(const line &a, const point &b)
{
	return (b.x - a.a.x) * (b.x - a.b.x) < 0;
}
point llintersect(const line &a, const line &b, int chk = 1)
{
	ft y = ((b.b.x - b.a.x) * (a.b * a.a) - (a.b.x - a.a.x) * (b.b * b.a)) / ((b.b - b.a) * (a.a - a.b));
	ft x;
	if (fabs(a.a.x - a.b.x) > 1e-6)
		x = (a.b * a.a - (a.a.y - a.b.y) * y) / (a.b.x - a.a.x);
	else
		x = (b.b * b.a - (b.a.y - b.b.y) * y) / (b.b.x - b.a.x);
	point ret(x, y);
	if (chk && (!inl(a, ret) || !inl(b, ret)))
		return inv;
	return ret;
}
struct circle
{
	point o;
	ft r;
	circle(const point &o, ft r):o(o), r(r){}
};
point pedal(const line &a, const point &b)
{
	vect pa = b - a.a, pb = b - a.b, pc = a.b - a.a;
	ft c = (-pa.ln() + pb.ln() - pc.ln()) / (2 * pc.len());
	return pc / pc.len() * c + a.b;
}
tpt clintersect(const line &a, const circle &b)
{
	vect p = pedal(a, b.o) - b.o;
	if (abs(p.len() - r) < 1e-9)
		return tpt(b.o + p, inv);
	if (p.len() > r)
		return tpt(inv, inv);
	vect t = p.r9().resize(sqrt(b.r * b.r - p.ln()));
	tpt ret(inv, inv);
	if (inl(a, b.o + p + t))
		ret.a = b.o + p + t;
	if (inl(a, b.o + p - t))
		ret.b = b.o + p - t;
	return ret;
}
tpt ccintersect(const circle &a, const circle &b)
{
	vect p = b.o - a.o;
	if ((a.r + b.r - p.len()) < 1e-9)
		return tpt(a.o + p.resize(a.r), inv);
	if (p.len() > a.r + b.r)
		return tpt(inv, inv);
	ft t = (a.r * a.r - b.r * b.r + p.ln()) / (2 * p.len());
	ft u = a.r * a.r - t * t;
	vect v = p.r9().resize(u);
	vect w = p.resize(t);
	return tpt(a.o + w + v, a.o + w - v);
}
line ls[111];
circle cs[111];
point ps[111];
const int lne = 1, crc = 2;
struct pt
{
	point p;
	int tp, num;
	pt(point p, int t, int n):p(p), tp(t), num(n){}
	bool operator<(const pt &a) const
	{
		return p.x < a.p.x;
	}
}pts[30303];
int np;
void add(const point &a, int t, int n)
{
	if (a != inv)
		pts[np++] = pt(a, t, n);
}
void add(const tpt &a, int t, int n)
{
	if (a.a != inv)
		add(a.a, t, n);
	if (a.b != inv)
		add(a.b, t, n);
}
int main()
{
	int n;
	ft r;
	scanf("%d%lf", &n, &r);
	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &ps[i].x, &ps[i].y);
	for (int i = 0; i < n - 1; i++)
		ls[i + 1] = line(ps[i] + (ps[i + 1] - ps[i]).r9().resize(r), ps[i + 1] + (ps[i + 1] - ps[i]).r9().resize(r));
	for (int j = 0; j < n; j++)
		cs[i] = circle(ps[i], r);
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			add(llintersect(ls[i], ls[j]), lne, j);
			add(clintersect(ls[i], cs[j]), crc, j);
			add(clintersect(ls[j], cs[i]), lne, j);
			add(ccintersect(cs[i], cs[j]), crc, j);
		}
//	add(clintersect(ls[1], cs[0]), lne, 1);
	sort(pts, pts + np);
	int nwt = lne;
	point nwp = ls[1].a;
	for (int i = 0; i < np; i++)
	{
		ls
	}
	return 0;
}
