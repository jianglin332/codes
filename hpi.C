#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#define pi 3.1415926535897932
#define eps 1e-15
#define POL 1
#define RECT 2
using namespace std;
double dmod(double a, double b)
{
	return fmod(fmod(a, b) + b, b);
}
inline bool iz(double a)
{
	if (a >= -eps && a <= eps)
		return true;
	return false;
}
double abs(double a)
{
	return a >= 0 ? a : -a;
}
struct vect
{
	double x, y, r, theta;
	bool isAv;
	int pol;
	vect()
	{
		x = y = r = theta = 0;
		isAv = 1;
		pol = 3;
	}
	vect(bool a)
	{
		x = y = r = theta = pol = 0;
		isAv = a;
	}
	void upd()
	{
		if (pol == RECT)
		{
			r = sqrt(x * x + y * y);
			if (iz(r))
				theta += pi / 2;
			else
				theta = atan2(y, x);
		}
		else if (pol == POL)
		{
			x = r * cos(theta);
			y = r * sin(theta);
		}
		pol = 3;
	}
	vect(double a, double b, int c = RECT)
	{
		isAv = 1;
		if (c == RECT)
		{
			pol = RECT;
			x = a;
			y = b;
		}
		else if (c == POL)
		{
			pol = POL;
			r = a;
			theta = b;
		}
		upd();
	}
	vect operator + (const vect &a)
	{
		return vect(x + a.x, y + a.y);
	}
	vect operator - (const vect &a)
	{
		return vect(x - a.x, y - a.y);
	}
	vect operator / (const double a)
	{
		return vect(x / a, y / a);
	}
	vect rotate(double _theta)
	{
		return vect(r, theta + _theta, POL);
	}
	vect to1()
	{
		return vect(1, theta, POL);
	}
	vect trans(double _x, double _y)
	{
		return vect(x + _x, y + _y);
	}
} vzero = 1, NotAv = 0;
typedef vect point;
struct edge
{
	point pnt;
	vect vct;
	edge(){}
	edge(point a, point b, bool c = 0)
	{
		if (c)
		{
			pnt = a;
			vct = b;
		}
		else
		{
			pnt = a;
			vct = b - a;
		}
	}
	point p2()
	{
		return pnt + vct;
	}
	edge rotate(double theta)
	{
		return edge(pnt.rotate(theta), vct.rotate(theta), 1);
	}
	edge trans(double x, double y)
	{
		return edge(pnt + point(x, y), vct, 1);
	}
};
struct circle
{
	point o;
	double r;
	circle(point a, double b)
	{
		o = a;
		r = b;
	}
};
struct twopoint
{
	int n;
	point a, b;
	twopoint()
	{
		n = 0;
		a = b = NotAv;
	}
	twopoint(point c)
	{
		a = c;
		n = 1;
	}
	twopoint(point c, point d)
	{
		a = c;
		b = d;
		n = 2;
		if (a.x > b.x)
			swap(a, b);
		if (a.x == b.x && a.y > b.y)
			swap(a, b);
	}
}tpzero;
bool isPara(vect a, vect b)
{
	double ans = dmod(a.theta - b.theta, pi);
	if (iz(ans))
		return true;
	return false;
}
bool isCoin(vect a, vect b)
{
	double ans = dmod(a.theta - b.theta, pi * 2);
	if (iz(ans))
		return true;
	return false;
}
bool isRev(vect a, vect b)
{
	double ans = dmod(a.theta - b.theta + pi, pi * 2);
	if (iz(ans))
		return true;
	return false;
}
void to0(edge &a, edge &b)
{
	b.pnt = b.pnt - a.pnt;
	a.pnt = vzero;
	b = b.rotate(-a.vct.theta);
	a = a.rotate(-a.vct.theta);
}
point intersect(edge _a, edge _b, bool chk)
{
	edge a = _a;
	edge b = _b;
	to0(a, b);
	if (isPara(a.vct, b.vct))
		return NotAv;
	point c = b.pnt;
	point d = b.p2();
	double e = (d.x * c.y - d.y * c.x) / (c.y - d.y);
	if (chk)
		if (c.y * d.y > 0 || e < -eps || e > a.vct.x + eps)
			return NotAv;
	point ans(e, 0);
	ans = ans.rotate(_a.vct.theta);
	ans = ans + _a.pnt;
	return ans;
}
double dist(point a, point b)
{
	return (a - b).r;
}
bool inB(edge a, point b)
{
}
int main()
{
	double a1, a2, b1, b2, r1, r2;
	scanf("%lf%lf%lf%lf%lf%lf", &a1, &a2, &r1, &b1, &b2, &r2);
	twopoint a = ccintersect(circle(point(a1, a2), r1), circle(point(b1, b2), r2));
	if (a.n == 0)
	{
		printf("LLJJ");
	}
	else if (a.n >= 1)
	{
		printf("%.5lf %.5lf\n", a.a.x, a.a.y);
	}
	if (a.n == 2)
	{
		printf("%.5lf %.5lf", a.b.x, a.b.y);
	}
	return 0;
}

