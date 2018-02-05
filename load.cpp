#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>
using namespace std;
struct ed
{
	int to, nx;
}es[808080];
int hd[202020], sd[202020], ne;
int n, m, q;
void ae(int f, int t, int *h = hd)
{
	es[ne].to = t;
	es[ne].nx = h[f];
	h[f] = ne++;
	es[ne].to = f;
	es[ne].nx = h[t];
	h[t] = ne++;
}
int rd[101010];
int dfn[101010], low[101010], nfn;
int rp[101010];
int np = 101010;
stack<int> st;
int tarjan(int nw, int fa)
{
	dfn[nw] = low[nw] = ++nfn;
	st.push(nw);
	for (int i = hd[nw]; i != -1; i = es[i].nx)
		if (es[i].to != fa)
		{
			if (!dfn[es[i].to])
				low[nw] = min(low[nw], tarjan(es[i].to, nw));
			else
				low[nw] = min(low[nw], dfn[es[i].to]);
		}
	if (low[nw] >= dfn[fa])
	{
		while (st.top() != nw)
		{
			int t = st.top();
			st.pop();
			if (!rp[t])
				rp[t] = np;
			else
				ae(np, t, sd);
		}
		st.pop();
		if (rp[nw])
			ae(nw, np, sd);
		else
			rp[nw] = np;
		ae(np, fa, sd);
		rp[fa] = fa;
		np++;
	}
	return low[nw];
}
int ff[202020][20];
int d[202020];
void dfs(int a, int faa, int ds)
{
	d[a] = ds;
	int fa = ff[a][0] = faa;
	for (int i = 0; i < 19; i++)
	{
		if (fa == -1 || ff[fa][i] == -1)
			break;
		ff[a][i + 1] = ff[fa][i];
		fa = ff[fa][i];
	}
	for (int i = sd[a]; i != -1; i = es[i].nx)
		if (es[i].to != faa)
			dfs(es[i].to, a, ds + 1);
}
int lca(int a, int b)
{
	if (d[a] < d[b])
		swap(a, b);
	for (int i = 19; i >= 0; i--)
		if (d[a] - (1 << i) >= d[b])
			a = ff[a][i];
	if (a == b)
		return a;
	for (int i = 19; i >= 0; i--)
		if (ff[a][i] != ff[b][i])
			a = ff[a][i], b = ff[b][i];
	return ff[a][0];
}
int vl[202020];
void link(int a, int b)
{
	rd[a]++, rd[b]++;
	a = rp[a], b = rp[b];
	if (a == b)
		return;
	int pr = lca(a, b);
	vl[a]++, vl[b]++;
	vl[pr]--, vl[ff[pr][0]]--;
}
int dfs(int a, int fa)
{
	for (int i = sd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa)
			vl[a] += dfs(es[i].to, a);
	return vl[a];
}
int main()
{
	memset(hd, -1, sizeof(hd));
	memset(sd, -1, sizeof(sd));
	memset(ff, -1, sizeof(ff));
	freopen("load.in", "r", stdin);
	freopen("load.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ae(a, b);
	}
	tarjan(1, 0);
	dfs(0, -1, 1);
	for (int i = 0; i < q; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		link(a, b);
	}
	dfs(0, -1);
	for (int i = 1; i <= n; i++)
		if (rp[i] == i)
			printf("%d\n", vl[i]);
		else
			printf("%d\n", rd[i]);
	return 0;
}
