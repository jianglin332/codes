#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn = 202020;
int best[maxn], fa[maxn], semi[maxn], idom[maxn];
int dfn[maxn], tg[maxn], nfn;
int st[maxn];
int gf(int a)
{
	int ns = 0;
	while (fa[a] != a)
	{
		st[++ns] = a;
		a = fa[a];
	}
	int mx = best[a];
	for (int i = ns; i; i--)
	{
		if (dfn[semi[mx]] > dfn[semi[best[st[i]]]])
			mx = best[st[i]];
		fa[st[i]] = a;
		best[st[i]] = mx;
	}
	return mx;
}
struct ed
{
	int to, nx;
}es[1010101];
int hd[202020], sd[202020], xd[202020], f[202020], ne;
void ae(int f, int t, int *h)
{
	es[ne].to = t;
	es[ne].nx = h[f];
	h[f] = ne++;
}
int r;
void dfs(int a)
{
	dfn[a] = ++nfn;
	tg[nfn] = a;
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (!dfn[es[i].to])
			dfs(es[i].to), f[es[i].to] = a;
}
int sz[maxn], hv[maxn], tp[maxn], d[maxn];
int mn[maxn];
void tarjan()
{
	dfs(r);
	for (int i = nfn; i >= 2; i--)
	{
		int now = tg[i];
		for (int j = sd[now]; j != -1; j = es[j].nx)
		{
			if (!dfn[es[j].to])
				continue;
			int t = gf(es[j].to);
			if (dfn[semi[now]] > dfn[semi[t]])
				semi[now] = semi[t];
		}
		ae(semi[now], now, xd);
		fa[now] = f[now];
		now = tg[i - 1];
		for (int j = xd[now]; j != -1; j = es[j].nx)
		{
			int nw = es[j].to;
			int t = gf(nw);
			if (semi[t] == now)
				idom[nw] = now;
			else
				idom[nw] = t;
		}
	}
	for (int i = 2; i <= nfn; i++)
	{
		int now = tg[i];
		if (idom[now] != semi[now])
			idom[now] = idom[idom[now]];
		d[now] = d[idom[now]] + 1;
		mn[now] = min(mn[now], mn[idom[now]]);
	}
	for (int i = nfn; i >= 2; i--)
	{
		int now = tg[i];
		sz[idom[now]] += ++sz[now];
		if (sz[now] > sz[hv[idom[now]]])
			hv[idom[now]] = now;
	}
	tp[tg[1]] = tg[1];
	for (int i = 2; i <= nfn; i++)
	{
		int now = tg[i];
		if (hv[idom[now]] != now)
			tp[now] = now;
		else
			tp[now] = tp[idom[now]];
	}
}
int lca(int a, int b)
{
	while (tp[a] != tp[b])
	{
		if (d[tp[a]] < d[tp[b]])
			swap(a, b);
		a = idom[tp[a]];
	}
	return d[a] < d[b] ? a : b;
}
int main()
{
	int n, m;
	scanf("%d%d%d", &n, &m, &r);
	memset(hd, -1, sizeof(hd));
	memset(sd, -1, sizeof(sd));
	memset(xd, -1, sizeof(xd));
	for (int i = 1; i <= n; i++)
		best[i] = fa[i] = semi[i] = i;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		ae(u, v, hd), ae(v, u, sd);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", mn + i);
	tarjan();
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int t, w, l = -1;
		scanf("%d%d", &t, &w);
		for (int i = 0; i < t; i++)
		{
			int f;
			scanf("%d", &f);
			if (!dfn[f])
				continue;
			f = idom[f];
			if (l == -1)
				l = f;
			else
				l = lca(f, l);
		}
		if (l == -1)
			printf("0\n");
		else if (mn[l] > w)
			printf("1\n");
		else
			printf("%d\n", mn[l]);
	}
	return 0;
}
