#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct ed
{
	int to, nx, l;
}es[404040];
int hd[202020], ne;
int n, k;
void ae(int f, int t, int l)
{
	es[ne].to = t;
	es[ne].l = l;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
int dd[202020];
#define foreach(a, i) \
	for (int i = hd[a]; i != -1; i = es[i].nx) \
		if (es[i].to != fa && !dd[es[i].to])
#define to(i) es[i].to
int gs(int a, int fa = 0)
{
	int sz = 1;
	foreach(a, i)
		sz += gs(to(i), a);
	return sz;
}
int mn, tg, sz;
int gm(int a, int fa = 0)
{
	int ss = 0, ms = 0;
	foreach(a, i)
	{
		int st = gm(to(i), a);
		ms = max(ms, st);
		ss += st;
	}
	ms = max(sz - 1 - ss, ms);
	if (ms < mn)
		mn = ms, tg = a;
	return ss + 1;
}
int gc(int a)
{
	sz = gs(a);
	mn = 0x23333333;
	gm(a);
	return tg;
}
long long ans;
int ds[202020];
int gen(int a, int fa, int d, int nw)
{
	ds[nw++] = d;
	foreach(a, i)
		nw = gen(to(i), a, d + es[i].l, nw);
	return nw;
}
void dfs(int a)
{
	a = gc(a);
	dd[a] = 1;
	int fa = 0;
	foreach(a, i)
		dfs(to(i));
	dd[a] = 0;
	int st = 0;
	foreach(a, i)
	{
		int ed = gen(to(i), a, es[i].l, st);
		int e = ed - 1;
		sort(ds + st, ds + ed);
		for (int i = st; i < ed; i++)
		{
			while (i < e && ds[i] + ds[e] > k)
				e--;
			if (i >= e)
				break;
			ans -= e - i;
		}
		st = ed;
	}
	sort(ds, ds + st);
	int e = st - 1;
	for (; e >= 0; e--)
		if (ds[e] <= k)
		{
			ans += e + 1;
			break;
		}
	for (int i = 0; i < st; i++)
	{
		while (i < e && ds[i] + ds[e] > k)
			e--;
		if (i >= e)
			break;
		ans += e - i;
	}
}
int main()
{
	scanf("%d%d", &n, &k);
	memset(hd, -1, sizeof(hd));
	for (int i = 1; i < n; i++)
	{
		int u, v, f;
		scanf("%d%d%d", &u, &v, &f);
		ae(u, v, f), ae(v, u, f);
	}
	dfs(1);
	printf("%lld", ans);
}
