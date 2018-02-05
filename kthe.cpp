#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
using namespace std;
int g()
{
	int r;
	scanf("%d", &r);
	return r;
}
int n, m;
struct tp
{
	int l, r, k, id;
	long long ans;
	bool operator<(const tp &a) const
	{
		return id < a.id;
	}
}qs[101010];
struct dt
{
	int p;
	long long v;
	bool operator<(const dt &a) const
	{
		return v < a.v;
	}
}ds[101010];
int bit[101010];
const long long inf = 3e9;
#define lb(x) ((x) & -(x))
void add(int p, int v)
{
	while (p <= n)
		bit[p] += v, p += lb(p);
}
int qry(int p)
{
	int r = 0;
	while (p)
		r += bit[p], p -= lb(p);
	return r;
}
int pos;
void work(int ql, int qr, long long l, long long r)
{
	if (l == r)
	{
		for (int i = ql; i <= qr; i++)
			qs[i].ans = l;
		return;
	}
	long long mid = (l + r) / 2;
	while (pos < n && ds[pos + 1].v <= mid)
		add(ds[++pos].p, 1);
	while (pos && ds[pos].v > mid)
		add(ds[pos--].p, -1);
	int n1 = ql, n2 = qr;
	while (n1 <= n2)
	{
		if (qry(qs[n1].r) - qry(qs[n1].l - 1) >= qs[n1].k)
			n1++;
		else
			swap(qs[n1], qs[n2]), n2--;
	}
	if (ql <= n2)
		work(ql, n2, l, mid);
	if (n1 <= qr)
		work(n1, qr, mid + 1, r);
}
void work()
{
	memset(bit, 0, sizeof(bit));
	memset(ds, 0, sizeof(ds));
	memset(qs, 0, sizeof(qs));
	pos = 0;
	n = g(), m = g();
	for (int i = 1; i <= n; i++)
		ds[i].v = g(), ds[i].v += inf, ds[i].p = i;
	for (int i = 1; i <= m; i++)
		qs[i].l = g(), qs[i].r = g(), qs[i].k = g(), qs[i].id = i;
	sort(ds + 1, ds + n + 1);
	work(1, m, 0, inf * 2);
	sort(qs + 1, qs + m + 1);
	for (int i = 1; i <= m; i++)
		printf("%d\n", int(qs[i].ans - inf));
}
int main()
{
	int t = g();
	for (int i = 0; i < t; i++)
		work();
	return 0;
}
