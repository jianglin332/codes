#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct node
{
	int lch, rch;
	int s;
} ns[2020202];
int root[101010];
int nn = 1;
int alloc(int vl, int lch = 0, int rch = 0)
{
	ns[nn].s = vl;
	ns[nn].lch = lch;
	ns[nn].rch = rch;
	return nn++;
}
int mkt(int l, int r)
{
	if (l == r)
		return alloc(0);
	return alloc(0, mkt(l, (l + r) / 2), mkt((l + r) / 2 + 1, r));
}
int ins(int nw, int vl, int l, int r)
{
	if (l == r)
		return alloc(ns[nw].s + 1);
	int mid = (l + r) / 2;
	if (vl <= mid)
	{
		int t = ins(ns[nw].lch, vl, l, mid);
		return alloc(ns[t].s + ns[ns[nw].rch].s, t, ns[nw].rch);
	}
	else
	{
		int t = ins(ns[nw].rch, vl, mid + 1, r);
		return alloc(ns[t].s + ns[ns[nw].lch].s, ns[nw].lch, t);
	}
}
int qry(int st, int ed, int k, int l, int r)
{
	if (l == r)
		return l;
	int ls = ns[ns[ed].lch].s - ns[ns[st].lch].s;
	if (ls < k)
		return qry(ns[st].rch, ns[ed].rch, k - ls, (l + r) / 2 + 1, r);
	else
		return qry(ns[st].lch, ns[ed].lch, k, l, (l + r) / 2);
}
int a[101010], pos[101010], rk[101010];
bool cmp(const int x, const int y)
{
	return a[x] < a[y];
}
void work()
{
	nn = 1;
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i), pos[i] = i;
	sort(pos + 1, pos + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		rk[pos[i]] = i;
	root[0] = mkt(1, n);
	for (int i = 1; i <= n; i++)
		root[i] = ins(root[i - 1], rk[i], 1, n);
	for (int i = 0; i < m; i++)
	{
		int s, t, k;
		scanf("%d%d%d", &s, &t, &k);
		printf("%d\n", a[pos[qry(root[s - 1], root[t], k, 1, n)]]);
	}
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		work();
}
