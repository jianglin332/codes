#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <algorithm>
using namespace std;
char buf[6060606];
int g()
{
	static char *n = buf;
	while (!isdigit(*n))
		n++;
	int r = 0;
	while (isdigit(*n))
		r = r * 10 + *(n++) - '0';
	return r;
}
int cl[33][1010], cr[33][1010];
struct qry
{
	int d, e, n, ans;
	bool operator<(const qry &a) const
	{
		return d < a.d;
	}
} qs[303030];
bool cmp(const qry &a, const qry &b)
{
	return a.n < b.n;
}
int a[1010], b[1010], c[1010];
int now[1010], tmp[1010];
#define gb(x) ((x - 1) / bs + 1)
#define st(x) ((x - 1) * bs + 1)
#define ed(x) ((x) * bs)
void add(int *now, int j)
{
	int d = 1, f = c[j];
	while (f)
	{
		if (d > f)
			d = f;
		int cs = d * a[j], bn = d * b[j];
		for (int k = 1000; k >= cs; k--)
			now[k] = max(now[k], now[k - cs] + bn);
		f -= d;
		d <<= 1;
	}
}
int main()
{
	freopen("bag.in", "r", stdin);
	freopen("bag.out", "w", stdout);
	fread(buf, 1, 6060606, stdin);
	int n = g();
	for (int i = 1; i <= n; i++)
		a[i] = g(), b[i] = g(), c[i] = g();
	int bs = sqrt(n);
	int nb = gb(n);
	for (int i = 1; i <= nb; i++)
	{
		int lm = min(ed(i), n);
		for (int j = st(i); j <= lm; j++)
			add(now, j);
		memcpy(cl[i], now, sizeof(now));
	}
	memset(now, 0, sizeof(now));
	for (int i = nb; i; i--)
	{
		int lm = min(ed(i), n);
		for (int j = st(i); j <= lm; j++)
			add(now, j);
		memcpy(cr[i], now, sizeof(now));
	}
	int q = g();
	for (int i = 0; i < q; i++)
		qs[i].d = g() + 1, qs[i].e = g(), qs[i].n = i;
	sort(qs, qs + q);
	int nowb = 0, np = 1, lp = 0;
	for (int i = 0; i < q; i++)
	{
		int bl = gb(qs[i].d);
		if (nowb != bl)
		{
			nowb = bl;
			memset(now, 0, sizeof(now));
			int *a = cl[bl - 1], *b = cr[bl + 1];
			for (int j = 0; j <= 1000; j++)
				for (int k = 0; k <= j; k++)
					now[j] = max(a[k] + b[j - k], now[j]);
			np = st(bl);
		}
		if (qs[i].d == lp)
		{
			qs[i].ans = tmp[qs[i].e];
		}
		else
		{
			while (np < qs[i].d)
				add(now, np++);
			memcpy(tmp, now, sizeof(now));
			int lm = min(ed(bl), n);
			for (int j = qs[i].d + 1; j <= lm; j++)
				add(tmp, j);
			qs[i].ans = tmp[qs[i].e];
			lp = qs[i].d;
		}
	}
	sort(qs, qs + q, cmp);
	for (int i = 0; i < q; i++)
		printf("%d\n", qs[i].ans);
}
