#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
struct rd
{
	int c, d, p, x, y, vl;
	bool operator<(const rd &a) const
	{
		if (c != a.c)
			return c < a.c;
		if (d != a.d)
			return d < a.d;
		return p < a.p;
	}
}rs[101010];
struct ed
{
	int to, nx, n;
}es[101010];
bool cmp(const rd &a, const rd &b)
{
	if (a.c == b.c)
		return a.p < b.p;
	else
		return a.c < b.c;
}
int hd[101010], ne;
void ae(int f, int t, int n)
{
	es[ne].to = t;
	es[ne].nx = hd[f];
	es[ne].n = n;
	hd[f] = ne++;
}
int n, m, nt;
int fa[101010], dep[101010];
int gf(int a)
{
	int f = a;
	while (f != fa[f])
		f = fa[f];
	int r = a;
	while (a != f)
	{
		int o = fa[a];
		fa[a] = f;
		a = o;
	}
	return f;
}
void merge(int a, int b)
{
	if (dep[a] == dep[b])
		dep[a]++;
	if (dep[a] < dep[b])
		fa[a] = b;
	else
		fa[b] = a;
}
void kruskal()
{
	for (int i = m - 1; i >= 0; i--)
	{
		int fx = gf(rs[i].x);
		int fy = gf(rs[i].y);
		if (fx == fy)
			continue;
		merge(fx, fy);
		rs[i].vl = 1;
		ae(rs[i].x, rs[i].y, rs[i].p);
		ae(rs[i].y, rs[i].x, rs[i].p);
	}
}
int c[101010];
int d[101010];
int nx[101010];
int fe[101010];
int g[101010];
int f[101010][20];
int mnn[101010][20];
void dfs(int nw, int par, int dp)
{
	printf("%d to %d\n", par, nw);
	int fa = f[nw][0] = par;
	if (nw != 1)
		mnn[nw][0] = c[fe[nw]];
	for (int i = 1; i < 20; i++)
	{
		if (fa == -1 || f[fa][i - 1] == -1)
			break;
		f[nw][i] = f[fa][i - 1];
		mnn[nw][i] = min(mnn[nw][i - 1], mnn[fa][i - 1]);
		fa = f[fa][i - 1];
	}
	d[nw] = dp;
	nx[nw] = par;
	for (int i = hd[nw]; i != -1; i = es[i].nx)
		if (es[i].to != par)
		{
			fe[es[i].to] = es[i].n;
			dfs(es[i].to, nw, dp + 1);
		}
}
int lca(int a, int b, int v)
{
	if (d[a] < d[b])
		swap(a, b);
	printf("%d %d %d: ", a, b, c[v]);
	int mn = 0x7fffffff;
	for (int i = 20; i >= 0; i--)
		if (d[a] - (1 << i) >= d[b])
		{
			mn = min(mn, mnn[a][i]);
			a = f[a][i];
		}
	if (a == b)
	{
		printf("%d %d\n", mn, a);
		if (mn > c[v])
			return -1;
		return a;
	}
	for (int i = 20; i >= 0; i--)
		if (f[a][i] != f[b][i])
		{
			mn = min(mn, min(mnn[a][i], mnn[b][i]));
			a = f[a][i], b = f[b][i];
		}
	mn = min(mn, min(mnn[a][0], mnn[b][0]));
	printf("%d %d\n", mn, f[a][0]);
	if (mn > c[v])
		return -1;
	return f[a][0];
}
void cover(int a, int b, int v)
{
	while (d[a] < d[b])
	{
		if (g[fe[b]] == -1 && c[fe[b]] == c[v])
		{
			g[fe[b]] = v;
		}
		int o = nx[b];
		nx[b] = a;
		b = o;
	}
}
struct tp
{
	int a;
	tp(int b)
	{
		a = b;
	}
	bool operator<(const tp &b) const
	{
		return g[a] > g[b.a];
	}
};
int main()
{
	scanf("%d%d", &n, &m);
	memset(g, -1, sizeof(g));
	memset(f, -1, sizeof(f));
	memset(mnn, 0x7f, sizeof(mnn));
	memset(hd, -1, sizeof(hd));
	for (int i = 0; i < m; i++)
	{
		int x, y, cc, d;
		scanf("%d%d%d%d", &x, &y, &cc, &d);
		c[i] = rs[i].c = cc;
		rs[i].d = d;
		rs[i].p = i;
		rs[i].x = x;
		rs[i].y = y;
		fa[i] = i;
	}
	sort(rs, rs + m);
	kruskal();
	dfs(1, -1, 1);
	sort(rs, rs + m, cmp);
	for (int i = m - 1; i >= 0; i--)
		if (!rs[i].vl)
		{
			int fa = lca(rs[i].x, rs[i].y, rs[i].p);
			if (fa == -1)
				continue;
			cover(fa, rs[i].x, rs[i].p);
			cover(fa, rs[i].y, rs[i].p);
		}
	priority_queue<tp> q;
	priority_queue<int, vector<int>, greater<int> > q2;
	for (int i = 0; i < m; i++)
		if (g[i] != -1)
			q.push(tp(i));
		else
			q2.push(i);
	while (!q2.empty())
	{
		int nw = q2.top();
		q2.pop();
		printf("%d ", nw + 1);
		while (!q.empty() && g[q.top().a] <= nw)
			q2.push(q.top().a), q.pop();
	}
}
