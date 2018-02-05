#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
int old[202020], olf[202020], num[202020], ns;
int cd[202020];
int f[202020], d[202020], nu, un;
int n;
void rev()
{
	while (ns >= 0)
		cd[num[ns]] = 0, f[num[ns]] = olf[ns], d[num[ns]] = old[ns], ns--;
	nu = un;
}
void clr()
{
	rev();
	for (int i = 1; i <= n; i++)
		f[i] = i, d[i] = 0;
	un = nu = n;
}
void set(int a, int b, int c, int e = -1)
{
	if (c && !cd[a])
	{
		cd[a] = 1, num[++ns] = a, olf[ns] = f[a], old[ns] = d[a];
	}
	f[a] = b;
	if (e != -1)
		d[a] = e;
}
int gf(int a, int c)
{
	int fa = a;
	while (fa != f[fa])
		fa = f[fa];
	while (a != fa)
	{
		int o = f[a];
		set(a, fa, c);
		a = o;
	}
	return fa;
}
void cn(int a, int b, int c)
{
	int fa = gf(a, c), fb = gf(b, c);
	if (fa == fb)
		return;
	if (d[fa] < d[fb])
		swap(fa, fb);
	if (d[fa] == d[fb])
		set(fa, fa, c, d[fa] + 1);
	set(fb, fa, c);
	nu--;
	if (!c)
		un--;
}
int bs;
struct qry
{
	int l, r, n, ans;
	bool operator<(const qry &a) const
	{
		if (l / bs == a.l / bs)
			return r < a.r;
		return l / bs < a.l / bs;
	}
}qs[202020];
int x[202020], y[202020];
bool cmp(const qry &a, const qry &b)
{
	return a.n < b.n;
}
void work()
{
	int m, q;
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", x + i, y + i);
	for (int i = 0; i < q; i++)
		scanf("%d%d", &qs[i].l, &qs[i].r), qs[i].n = i;
	bs = sqrt(n) + 1;
	sort(qs, qs + q);
	int prev = -1, to = 0;
	for (int i = 0; i < q; i++)
	{
		int bn = qs[i].l / bs;
		if (bn != prev)
			clr(), to = (bn + 1) * bs, prev = bn;
		rev();
		if (bn == qs[i].r / bs)
			for (int j = qs[i].l; j <= qs[i].r; j++)
				cn(x[j], y[j], 1);
		else
		{
			for (; to <= qs[i].r; to++)
				cn(x[to], y[to], 0);
			for (int j = qs[i].l; j < (bn + 1) * bs; j++)
				cn(x[j], y[j], 1);
		}
		qs[i].ans = nu;
	}
	sort(qs, qs + q, cmp);
	for (int i = 0; i < q; i++)
		printf("%d\n", qs[i].ans);
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		work();
	return 0;
}
