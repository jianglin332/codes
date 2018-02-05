#include <cstdio>
#define eps 1e-8
#include <algorithm>
using std::swap;
struct vec
{
	double v[12];
}x;
struct matrix
{
	vec a[12];
	double b[12];
	int nx;
}org;
double abs(double a)
{
	return a > 0 ? a : -a;
}
bool iz(const double a)
{
	if (a >= -eps && a <= eps)
		return 1;
	return 0;
}
void chk(matrix &d)
{
	for (int i = 0; i <= d.nx; i++)
		if (!d.a[i].v[i])
		{
			for (int j = i + 1; j <= d.nx; j++)
				if (d.a[j].v[i])
				{
					swap(d.a[i], d.a[j]);
					swap(d.b[i], d.b[j]);
				}
		}
}
void gen(matrix &d)
{
	double mt = -d.a[d.nx].v[d.nx];
	for (int i = 0; i < d.nx; i++)
	{
		if (iz(d.a[i].v[d.nx]))
			continue;
		double dv = d.a[i].v[d.nx];
		for (int j = 0; j < d.nx; j++)
		{
			d.a[i].v[j] *= mt;
			d.a[i].v[j] /= dv;
			d.a[i].v[j] += d.a[d.nx].v[j];
		}
		d.b[i] *= mt;
		d.b[i] /= dv;
		d.b[i] += d.b[d.nx];
	}
	d.nx--;
}
void solve(matrix m)
{
	matrix nw = m;
	if (m.nx == 0)
	{
		x.v[0] = m.b[0] / m.a[0].v[0];
		return;
	}
	gen(nw);
	solve(nw);
	x.v[m.nx] = m.b[m.nx];
	for (int i = 0; i < m.nx; i++)
		x.v[m.nx] -= m.a[m.nx].v[i] * x.v[i];
	x.v[m.nx] /= m.a[m.nx].v[m.nx];
}
int main()
{
	int n;
	scanf("%d", &n);
	org.nx = n - 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%lf", &org.a[i].v[j]);
	for (int i = 0; i < n; i++)
		scanf("%lf", &org.b[i]);
	chk(org);
	solve(org);
	for (int i = 0; i < n; i++)
		printf("%.2lf\n", x.v[i] + 0.00499);
	return 0;
}

