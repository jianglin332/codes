#include <cstdio>
#include <cmath>
#define pi 3.1415926535897932
struct cp
{
	double a, b;
	cp():a(0), b(0){}
	cp(double c, double d):a(c), b(d){}
	cp operator+(cp c)
	{
		return cp(a + c.a, b + c.b);
	}
	cp operator*(cp c)
	{
		return cp(a * c.a - b * c.b, a * c.b + b * c.a);
	}
};
struct cps
{
	int l;
	cp *v;
	cps(int le):l(le), v(new cp[le]){}
/*	~cps()
	{
		delete [] v;
	}
*/};
void fourier(cps src, cp phi)
{
	if (src.l == 1)
		return;
	int l = src.l, m = l / 2;
	cps a(m), b(m);
	for (int i = 0; i < m; i++)
		a.v[i] = src.v[i << 1], b.v[i] = src.v[(i << 1) + 1];
	fourier(a, phi * phi);
	fourier(b, phi * phi);
	cp w(1, 0);
	for (int k = 0; k <= 1; k++)
		for (int i = 0; i < m; i++, w = w * phi)
			src.v[i + k * m] = a.v[i] + (w * b.v[i]);
}
int main()
{
	int n;
	scanf("%d", &n);
	cps a(n);
	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &a.v[i].a, &a.v[i].b);
	fourier(a, cp(cos(2 * pi / n), sin(2 * pi / n)));
	for (int i = 0; i < n; i++)
	{
		printf("%.2lf %.2lf\n", a.v[i].a / n, a.v[i].b / n);
	}
}
