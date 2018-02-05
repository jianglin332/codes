#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct ed
{
	int fr, to, v;
	bool operator<(const ed &a) const
	{
		return v > a.v;
	}
}es[50505];
struct e
{
	int to, nx, v;
}ees[20202];
int ne;
int hd[10101];
void ae(int fr, int to, int v)
{
	ees[ne].to = to, ees[ne].v = v, ees[ne].nx = hd[fr];
	hd[fr] = ne++;
}
int fa[10101];
int gf(int a)
{
	int f = a;
	while (fa[f] != f)
		f = fa[f];
	while (a != f)
	{
		int o = fa[a];
		fa[a] = f;
		a = o;
	}
	return f;
}
int f[10101][20], mn[10101][20], vd[10101], nv, dep[10101];
void dfs(int nw, int fa)
{
	int nf = f[nw][0];
	vd[nw] = nv;
	dep[nw] = dep[fa] + 1;
	for (int i = 0; f[nf][i]; i++)
		f[nw][i + 1] = f[nf][i], mn[nw][i + 1] = min(mn[nw][i], mn[nf][i]), nf = f[nf][i];
	for (int i = hd[nw]; i != -1; i = ees[i].nx)
		if (ees[i].to != fa)
			f[ees[i].to][0] = nw, mn[ees[i].to][0] = ees[i].v, dfs(ees[i].to, nw);
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	memset(hd, -1, sizeof(hd));
	memset(mn, 0x23, sizeof(mn));
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &es[i].fr, &es[i].to, &es[i].v);
	sort(es, es + m);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 0; i < m; i++)
	{
		int af = gf(es[i].fr), bf = gf(es[i].to);
		if (af != bf)
		{
			ae(es[i].fr, es[i].to, es[i].v);
			ae(es[i].to, es[i].fr, es[i].v);
			fa[af] = bf;
		}
	}
	for (int i = 1; i <= n; i++)
		if (!vd[i])
			nv++, dfs(i, 0);
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (vd[x] != vd[y])
			printf("-1\n");
		else
		{
			if (dep[x] > dep[y])
				swap(x, y);
			int z = 0x23333333;
			for (int i = 15; dep[x] < dep[y] && i >= 0; i--)
			{
				if (dep[x] <= dep[y] - (1 << i))
				{
					z = min(z, mn[y][i]);
					y = f[y][i];
				}
			}
			if (x != y)
			{
				for (int i = 15; i >= 0; i--)
					if (f[x][i] != f[y][i])
						z = min(z, min(mn[x][i], mn[y][i])), x = f[x][i], y = f[y][i];
				z = min(z, min(mn[x][0], mn[y][0]));
			}
			printf("%d\n", z);
		}
	}
	return 0;
}
