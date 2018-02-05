#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>
using namespace std;
struct ed
{
	int to, nx;
}es[1010101];
int hd[101010], ne, sd[101010];
void ae(int f, int t)
{
	es[ne].to = t;
	es[ne].nx = hd[f];
	hd[f] = ne++;
	es[ne].to = f;
	es[ne].nx = sd[t];
	sd[t] = ne++;
}
int f[101010], mn[101010];
int st[101010], ns;
int gf(int a)
{
	int fa = a;
	ns = 0;
	while (f[fa] != fa)
	{
		st[++ns] = fa;
		fa = f[fa];
	}
	int m = mn[fa];
	for (int i = ns; i; i--)
		f[st[i]] = fa, mn[st[i]] = m = min(mn[st[i]], m);
	return fa;
}
int dfn[101010], par[101010], sq[101010], nfn;
void dfs(int nw)
{
	sq[++nfn] = nw;
	dfn[nw] = nfn;
	for (int i = hd[nw]; i != -1; i = es[i].nx)
		if (!dfn[es[i].to])
			dfs(es[i].to), par[es[i].to] = nw;
}
int semi[101010], idom[101010], y[101010];
int siz[101010], mu[101010];
stack<int> sr[101010];
int main()
{
	int n, m;
	memset(sd, -1, sizeof(sd));
	memset(hd, -1, sizeof(hd));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ae(a, b);
	}

	dfs(1);
	for (int i = 1; i <= n; i++)
		f[i] = i, semi[i] = i, mn[i] = dfn[i];
	for (int i = nfn; i > 1; i--)
	{
		int nw = sq[i];
		int tmp = 111111;
		for (int j = sd[nw]; j != -1; j = es[j].nx)
		{
			int to = es[j].to;
			if (!dfn[to])
				continue;
			gf(to);
			if (mn[to] < tmp) tmp = mn[to];
		}
		semi[nw] = sq[mn[nw] = tmp];
		int x = sq[i - 1];
		sr[semi[nw]].push(nw);
				f[nw] = par[nw];
		if (!x)
			continue;
		while (!sr[x].empty())
		{
			int t = sr[x].top();
			sr[x].pop();
			gf(t);
			if (semi[t] == semi[sq[mn[t]]])
				idom[t] = semi[t];
			else
				idom[t] = sq[mn[t]];
		}

	}
	for (int i = 2; i <= nfn; i++)
		if (idom[sq[i]] != semi[sq[i]])
			idom[sq[i]] = idom[idom[sq[i]]];
	for (int i = nfn; i > 1; i--)
		siz[idom[sq[i]]] += ++siz[sq[i]];
	siz[1]++;
	long long ans = (nfn - 1ll) * nfn / 2;
	for (int i = 1; i <= n; i++)
		if (idom[i] == 1)
			ans -= siz[i] * (siz[i] - 1ll) / 2;
//	for (int i = 2; i <= nfn; i++)
//		ans += mu[sq[i]] = (idom[sq[i]] == sq[1] ? siz[sq[1]] - siz[sq[i]] : mu[idom[sq[i]]]);
	printf("%lld", ans);
}

