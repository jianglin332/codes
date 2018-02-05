#include <stdio.h>
long long c[404040];
#define lowbit(x) ((x) & (-(x)))
int n;
void ins(int t, int u = 1)
{
	while (t <= n * 4 + 5)
		c[t] += u, t += lowbit(t);
}
int qry(int t)
{
	long long a = 0;
	while (t)
		a += c[t], t -= lowbit(t);
	return a;
}
struct node
{
	int l, r, par, size, now;
	int dfn1, dfn2, dfn3, dfn4;
}ns[101010];
int dfn = 1;
int dfs(int nd)
{
	ins(ns[nd].dfn1 = dfn++);
	ns[nd].dfn2 = dfn++;
	ns[nd].size = 1;
	if (ns[nd].l)
		ns[nd].size += dfs(ns[nd].l);
	ns[nd].dfn3 = dfn++;
	if (ns[nd].r)
		ns[nd].size += dfs(ns[nd].r);
	ns[nd].dfn4 = dfn++;
	return ns[nd].size;
}
int g(int x)
{
	if (x)
		return ns[x].size;
	return 0;
}
void chg(int x)
{
	if (!ns[x].now)
	{
		ins(ns[x].dfn2, g(ns[x].r));
		ins(ns[x].dfn3, -(g(ns[x].l) + g(ns[x].r)));
		ins(ns[x].dfn4, g(ns[x].l));
		ns[x].now = 1;
	}
	else
	{
		ins(ns[x].dfn2, -g(ns[x].r));
		ins(ns[x].dfn3, g(ns[x].l) + g(ns[x].r));
		ins(ns[x].dfn4, -g(ns[x].l));
		ns[x].now = 0;
	}
}
int main()
{
	int m;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int p, c, k;
		scanf("%d%d%d", &p, &c, &k);
		ns[c].par = p;
		if (k)
			ns[p].r = c;
		else
			ns[p].l = c;
	}
	int mx;
	for (int i = 1; i <= n; i++)
		if (!ns[i].par)
		{
			mx = i;
			break;
		}
	dfs(mx);
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		int t, x;
		scanf("%d%d", &t, &x);
		if (t == 1)
			printf("%d\n", qry(ns[x].dfn1) - 1);
		else
			chg(x);
	}
}
