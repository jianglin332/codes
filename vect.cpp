#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define POL 2
#define RECT 1
#define esp 1e-8
#define pi 3.1415926535897932
/*struct point
{
	double x, y;
	double
};*/
struct vect
{
	double x, y;
	double r, theta;
	int pol;
	bool isAv;
	void upd();
	vect()
	{
		x = y = r = theta = 0;
		pol = 3;
		isAv = 1;
	}
	vect(bool a)
	{
		x = y = r = theta = pol = 0;
		isAv = a;
	}
	vect(int _pol, double a, double b)
	{
		isAv = 1;
		pol = _pol;
		if (pol == POL)
		{
			r = a;
			theta = b;
		}
		else if (pol == RECT)
		{
			x = a;
			y = b;
		}
		upd();
	}
	vect trans(double x, double y);
	vect operator+(vect a);
	vect operator-(vect a);
	vect operator/(double a)
	{
		vect ans = (*this);
		ans.x /= a;
		ans.y /= a;
		ans.upd();
		return ans;
	}
} NotAv = 0, vzero;
typedef vect point;
struct edge
{
	vect vct;
	point pnt;
	edge(){}
	edge(point a, point b);
	point pntb()
	{
		return pnt + vct;
	}
};
void vect::upd()
{
	if (pol == 3)
		return;
	if (pol == RECT)
	{
		r = sqrt(x * x + y * y);
		if (r == 0)
			theta += pi / 2;
		else
			theta = atan2(y, x);
		pol = 3;
		return;
	}
	if (pol == POL)
	{
		x = r * cos(theta);
		y = r * sin(theta);
		pol = 3;
		return;
	}
	return;
}
vect rotate(vect a, double theta)
{
	vect ans = a;
	ans.pol = POL;
	ans.theta += theta;
	ans.upd();
	return ans;
}
edge rotate(edge a, double theta)
{
	edge ans = a;
	ans.vct = rotate(ans.vct, theta);
	ans.pnt = rotate(ans.pnt, theta);
	return ans;
}
vect to1(vect a)
{
	vect ans = a;
	ans.pol = POL;
	ans.r = 1;
	ans.upd();
	return ans;
}
bool isCoincide(vect a, vect b)
{
	if (fmod(fmod(a.theta - b.theta, pi * 2) + pi * 2, pi * 2) < esp && fmod(fmod(a.theta - b.theta, pi * 2) + pi * 2, pi * 2) > -esp)
		return true;
	return false;
}
bool isReverse(vect a, vect b)
{
	if (fmod(fmod(a.theta - b.theta + pi, pi * 2) + pi * 2, pi * 2) < esp && fmod(fmod(a.theta - b.theta + pi, pi * 2) + pi * 2, pi * 2) > -esp)
		return true;
	return false;
}
bool isPara(vect a, vect b)
{
	if (fmod(fmod(a.theta - b.theta, pi) + pi, pi) < esp && fmod(fmod(a.theta - b.theta, pi) + pi, pi) > -esp)
		return true;
	return false;
}
point point::trans(double _x, double _y)
{
	point ans = (*this);
	pol = RECT;
	ans.x += _x;
	ans.y += _y;
	ans.upd();
	return ans;
}
edge trans(edge a, double x, double y)
{
	edge ans = a;
	ans.pnt.trans(x, y);
	return ans;
}
vect vect::operator+(vect a)
{
	vect ans = (*this);
	ans.pol = RECT;
	ans.x += a.x;
	ans.y += a.y;
	ans.upd();
	return ans;
}
vect vect::operator-(vect a)
{
	vect ans = (*this);
	ans.pol = RECT;
	ans.x -= a.x;
	ans.y -= a.y;
	ans.upd();
	return ans;
}
edge::edge(point a, point b)
{
	vct = b - a;
	pnt = a;
}
void moveToZP(edge &a, edge &b)
{
	b.pnt = b.pnt - a.pnt;
	a.pnt = vzero;
	b = rotate(b, -a.vct.theta);
	a = rotate(a, -a.vct.theta);
}
point lintersect(edge _a, edge _b)
{
	edge a = _a;
	edge b = _b;
	if (isPara(a.vct, b.vct))
	{
		return NotAv;
	}
	moveToZP(a, b);
	point c = b.pnt;
	point d = b.pnt + b.vct;
	double t = (c.x * d.y - d.x * c.y) / (d.y - c.y);
	point ans;
	ans.pol = RECT;
	ans.x = t;
	ans.upd();
	ans = rotate(ans, _a.vct.theta);
	ans = ans.trans(_a.pnt.x, _a.pnt.y);
	return ans;
}
point intersect(edge _a, edge _b)
{
	edge a = _a;
	edge b = _b;
	if (isPara(a.vct, b.vct))
	{
		return NotAv;
	}
	moveToZP(a, b);
	point c = b.pnt;
	point d = b.pnt + b.vct;
	double t = (c.x * d.y - d.x * c.y) / (d.y - c.y);
	if (b.pnt.y * (b.pnt.y + b.vct.y) > 0)
	{
		return NotAv;
	}
	if (t < -esp || t > a.vct.x + esp)
		return NotAv;
	point ans;
	ans.pol = RECT;
	ans.x = t;
	ans.upd();
	ans = rotate(ans, _a.vct.theta);
	ans = ans.trans(_a.pnt.x, _a.pnt.y);
	return ans;
}
point midpoint(edge a)
{
	return a.pnt + (a.vct / 2);
}
edge bisect(point _a, point _m, point _b)
{
	vect a = to1(_a - _m);
	vect b = to1(_b - _m);
	edge ans;
	ans.pnt = _m;
	ans.vct = to1(a + b);
	return ans;
}
point project(point a, edge b)
{
	edge t;
	t.pnt = a;
	t.vct = rotate(b.vct, pi / 2);
	return lintersect(t, b);
}
int main()
{
	double a1, b1, c1, a2, b2, c2;
	scanf("%lf%lf%lf%lf%lf%lf", &a1, &a2, &b1, &b2, &c1, &c2);
	point a(RECT, a1, a2), b(RECT, b1, b2), c(RECT, c1, c2);
	edge bc(b, c);
	point mbc = midpoint(bc);
	point bs = lintersect(bisect(b, a, c), bc);
	point pa = project(a, bc);
	printf("%.2lf %.2lf\n%.2lf %.2lf\n%.2lf %.2lf\n", mbc.x, mbc.y, bs.x, bs.y, pa.x, pa.y);
	return 0;
}
