#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
struct ed
{
	int to, c, nx;
}es[(700 * 700 + 700  * 2) * 2];
int hd[1414], head[1414], d[1414], ne;
int S = 1411, T = 1412;
bool bfs()
{
	memset(d, 0, sizeof(d));
	d[S] = 1;
	queue<int> q;
	q.push(S);
	bool ret = 0;
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		ret |= nw == T;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (es[i].c && !d[es[i].to])
				d[es[i].to] = d[nw] + 1, q.push(es[i].to);
	}
	memcpy(head, hd, sizeof(hd));
	return ret;
}
int dinic(int a, int c)
{
	if (a == T)
		return c;
	int cc = c;
	for (int &i = head[a]; i != -1; i = es[i].nx)
		if (es[i].c && d[es[i].to] > d[a])
		{
			int t = dinic(es[i].to, min(es[i].c, c));
			if (t)
			{
				es[i].c -= t;
				es[i ^ 1].c += t;
				c -= t;
				if (!c)
					return cc;
			}
		}
	return cc - c;
}
struct td
{
	int to, nx;
}ts[202020];
int td[101010], nt;
void ab(int fr, int to)
{
	ts[nt].to = to;
	ts[nt].nx = td[fr];
	td[fr] = nt++;
}
void ae(int fr, int to, int c)
{
	es[ne].c = c;
	es[ne].to = to;
	es[ne].nx = hd[fr];
	hd[fr] = ne++;
	es[ne].c = 0;
	es[ne].to = fr;
	es[ne].nx = hd[to];
	hd[to] = ne++;
}
int f[101010][20];
int h[101010];
void dfs(int a)
{
	if (a != 1)
		h[a] = h[f[a][0]] + 1;
	for (int i = 0; i < 20; i++)
	{
		if (f[a][i] == -1)
			break;
		f[a][i + 1] = f[f[a][i]][i];
	}
	for (int i = td[a]; i != -1; i = ts[i].nx)
		if (ts[i].to != f[a][0])
			f[ts[i].to][0] = a, dfs(ts[i].to);
}
int lca(int a, int b)
{
	if (h[a] < h[b])
		swap(a, b);
	for (int i = 19; i >= 0; i--)
		if (h[a] - (1 << i) >= h[b])
			a = f[a][i];
	if (a == b)
		return a;
	for (int i = 19; i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
int bx[707], by[707], bj[707];
int gx[707], gy[707], gj[707];
const int inf = 1e9 + 7;
bool intersect(int b, int g)
{
	int ba = bx[b], bb = by[b];
	int ga = gx[g], gb = gy[g];
	int fb = lca(ba, bb), fg = lca(ga, gb);
	if (h[fb] < h[fg])
		return lca(ba, fg) == fg || lca(bb, fg) == fg;
	return lca(ga, fb) == fb || lca(gb, fb) == fb;
}
int main()
{
	memset(f, -1, sizeof(f));
	memset(hd, -1, sizeof(hd));
	memset(td, -1, sizeof(td));
	int n, m1, m2, ans = 0;
	scanf("%d%d%d", &n, &m1, &m2);
	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ab(a, b), ab(b, a);
	}
	dfs(1);
	for (int i = 0; i < m1; i++)
		scanf("%d%d%d", bx + i, by + i, bj + i), ans += bj[i];
	for (int i = 0; i < m2; i++)
		scanf("%d%d%d", gx + i, gy + i, gj + i), ans += gj[i];
	for (int i = 0; i < m1; i++)
		for (int j = 0; j < m2; j++)
			if (intersect(i, j))
				ae(i, j + m1, inf);
	for (int i = 0; i < m1; i++)
		ae(S, i, bj[i]);
	for (int i = 0; i < m2; i++)
		ae(i + m1, T, gj[i]);
	while (bfs())
		ans -= dinic(S, inf);
	printf("%d", ans);
	return 0;
}
