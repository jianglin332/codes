#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct ed
{
	int to, nx;
}es[101010];
int hd[101010], ne;
void ae(int f, int t)
{
	es[ne].to = t;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
int hv[101010], sz[101010], tp[101010], f[101010], end[101010], dfn[101010], nfn, n, q;
int df1(int a, int fa)
{
	sz[a] = 1;
	f[a] = fa;
	int mx = 0;
	for (int i = hd[a]; i != -1; i = es[i].nx)
	{
		int t = df1(es[i].to, a);
		sz[a] += t;
		if (t > mx)
			hv[a] = es[i].to, mx = t;
	}
	return sz[a];
}
void df2(int a, int fa)
{
	if (fa == -1 || hv[fa] != a)
		tp[a] = a;
	else
		tp[a] = tp[fa];
	dfn[a] = ++nfn;
	end[a] = sz[a] + dfn[a] - 1;
	if (hv[a])
		df2(hv[a], a);
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != hv[a])
			df2(es[i].to, a);
}
struct node
{
	node *lch, *rch;
	int l, r;
	int s;
	int lazy;
	int set(int a)
	{
		int os = s;
		s = a * (r - l + 1);
		lazy = a;
		return s - os;
	}
	void down()
	{
		if (lazy != -1)
			lch->set(lazy), rch->set(lazy), lazy = -1;
	}
	void upd()
	{
		s = lch->s + rch->s;
	}
	node(int l, int r):l(l), r(r)
	{
		lazy = s = 0;
		if (l == r)
			lch = rch = 0;
		else
			lch = new node(l, (l + r) / 2), rch = new node((l + r) / 2 + 1, r);
	}
} *root;
int set(int l, int r, int t, node *rt = root)
{
	if (l <= rt->l && rt->r <= r)
		return rt->set(t);
	int ret = 0;
	rt->down();
	if (l <= rt->lch->r)
		ret += set(l, r, t, rt->lch);
	if (r >= rt->rch->l)
		ret += set(l, r, t, rt->rch);
	rt->upd();
	return ret;
}
int ins(int a)
{
	int ret = 0;
	while (a != -1)
		ret += set(dfn[tp[a]], dfn[a], 1), a = f[tp[a]];
	return ret;
}
int del(int a)
{
	return -set(dfn[a], end[a], 0);
}
char s[11];
int main()
{
	memset(hd, -1, sizeof(hd));
	scanf("%d", &n);
	root = new node(1, n);
	for (int i = 1; i < n; i++)
	{
		int t;
		scanf("%d", &t);
		ae(t, i);
	}
	df1(0, -1), df2(0, -1);
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int t;
		scanf("%s%d", s, &t);
		printf("%d\n", s[0] == 'i' ? ins(t) : del(t));
	}
	return 0;
}
