#include <cstdio>
#include <algorithm>
using namespace std;
#include <cstring>
struct ed
{
	int to, nx;
}es[101010];
int fa[50505][20];
int hd[50505], ne;
int dep[50505];
int deg[50505];
int h[50505];
int f[50505][20], g[50505][20];
void ae(int a, int b)
{
	es[ne].to = a;
	es[ne].nx = hd[b];
	hd[b] = ne++;
}
void dfs1(int a)
{
	int f = fa[a][0];
	for (int i = 0; i < 20; i++)
		if (f != -1 && fa[f][i] != -1)
		{
			fa[a][i + 1] = fa[f][i];
			f = fa[f][i];
		}
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa[a][0])
		{
			deg[a]++;
			deg[es[i].to]++;
			fa[es[i].to][0] = a;
			dep[es[i].to] = dep[a] + 1;
			dfs1(es[i].to);
		}
}
void dfs2(int a)
{
	f[a][0] = deg[a];
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa[a][0])
		{
			dfs2(es[i].to);
			f[a][0] += f[es[i].to][0];
		}
	if (a == 0)
		f[a][0] = 0;
}
void dfs3(int a)
{
	int pr = fa[a][0];
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa[a][0])
			h[a] += f[es[i].to][0];
	if (pr == -1)
		g[a][0] = 0;
	else
	{
		g[a][0] = deg[pr];
		g[a][0] += g[pr][0];
		g[a][0] += h[pr] - f[a][0];
	}
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa[a][0])
			dfs3(es[i].to);
}
void dfs4(int a)
{
	for (int i = 0; i < 19; i++)
		if (fa[a][i + 1] != -1)
		{
			f[a][i + 1] = f[a][i] + f[fa[a][i]][i];
			g[a][i + 1] = g[a][i] + g[fa[a][i]][i];
		}
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa[a][0])
			dfs4(es[i].to);
}
int get(int fr, int to)
{
	int ret = 0;
	int md = min(dep[fr], dep[to]);
	for (int i = 19; i >= 0; i--)
	{
		if (dep[fr] - (1 << i) >= md)
		{
			ret += f[fr][i];
			fr = fa[fr][i];
		}
		if (dep[to] - (1 << i) >= md)
		{
			ret += g[to][i];
			to = fa[to][i];
		}
	}
	if (fr == to)
		return ret;
	for (int i = 19; i >= 0; i--)
	{
		if (fa[fr][i] != fa[to][i])
		{
			ret += f[fr][i] + g[to][i];
			fr = fa[fr][i];
			to = fa[to][i];
		}
	}
	return ret + f[fr][0] + g[to][0];
}
void work()
{
	memset(dep, 0, sizeof(dep));
	memset(deg, 0, sizeof(deg));
	memset(fa, -1, sizeof(fa));
	memset(hd, -1, sizeof(hd));
	memset(es, 0, sizeof(es));
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	memset(h, 0, sizeof(h));
	ne = 0;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		ae(x, y);
		ae(y, x);
	}
	dfs1(0);
	dfs2(0);
	dfs3(0);
	dfs4(0);
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int p;
		scanf("%d", &p);
		int ans = 0;
		int prev = -1;
		for (int j = 0; j <= p; j++)
		{
			int now;
			scanf("%d", &now);
			if (prev != -1)
				ans += get(prev, now);
			prev = now;
		}
		printf("%d.0000\n", ans);
	}
	printf("\n");
}
int main()
{
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		work();
	return 0;
}
