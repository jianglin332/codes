#include <cstdio>
#include <cctype>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef unsigned int ui;
int g()
{
	int r = 0;
	char c = 0;
	while (!isdigit(c = getchar()));
	r = c - '0';
	while (isdigit(c = getchar()))
		r = r * 10 + c - '0';
	return r;
}
struct node
{
	node *lch, *rch;
	ui t[7];
	ui v, d;
	int l, r;
	node *mn;
	int h;
	node(int a, int b)
	{
		memset(t, 0, sizeof(t));
		l = r = v = a;
		t[1] = d = b;
		h = rand();
		lch = rch = 0;
		mn = this;
	}
} *root;
inline ui gt(node *a, int b)
{
	if (b < 0)
		return 0;
	return (a ? a->t[b] : 0);
}
void upd(node *rt)
{
	if (!rt)
		return;
	rt->mn = rt;
	if (rt->lch)
	{
		rt->l = rt->lch->l;
		if (rt->mn->d > rt->lch->mn->d)
			rt->mn = rt->lch->mn;
	}
	else
		rt->l = rt->v;
	if (rt->rch)
	{
		rt->r = rt->rch->r;
		if (rt->mn->d > rt->rch->mn->d)
			rt->mn = rt->rch->mn;
	}
	else
		rt->r = rt->v;
	rt->t[1] = gt(rt->lch, 1) + gt(rt->rch, 1) + rt->d;
	for (int i = 2; i < 7; i++)
	{
		rt->t[i] = gt(rt->lch, i) + gt(rt->rch, i) + rt->d * (gt(rt->lch, i - 1) + gt(rt->rch, i - 1));
		for (int j = 1; j < i; j++)
			rt->t[i] += gt(rt->lch, j) * gt(rt->rch, i - j);
	}
}
void rot(node *&rt)
{
	if (rt->lch && rt->h < rt->lch->h)
	{
		node *t = rt->lch;
		rt->lch = t->rch;
		upd(rt);
		t->rch = rt;
		rt = t;
		upd(rt);
	}
	else if (rt->rch && rt->h < rt->rch->h)
	{
		node *t = rt->rch;
		rt->rch = t->lch;
		upd(rt);
		t->lch = rt;
		rt = t;
		upd(rt);
	}
}
void ins(int v, int d, node *&rt = root)
{
	if (!rt)
	{
		rt = new node(v, d);
		return;
	}
	if (rt->v < v)
		ins(v, d, rt->rch);
	else
		ins(v, d, rt->lch);
	upd(rt);
	rot(rt);
}
node ans(0, 0);
ui f[7];
void merge(node *b)
{
	for (int i = 1; i < 7; i++)
	{
		f[i] = ans.t[i] + b->t[i];
		for (int j = 1; j < i; j++)
			f[i] += ans.t[j] * b->t[i - j];
	}
	for (int i = 1; i < 7; i++)
		ans.t[i] = f[i];
}
void merge2(ui a)
{
	for (int i = 6; i > 1; i--)
	{
		ans.t[i] += ans.t[i - 1] * a;
	}
	ans.t[1] += a;
}
void qry(int l, int r, node *el, node *rt = root)
{
	if (!rt)
		return;
	if (l <= rt->l && r >= rt->r && rt->mn != el)
	{
		merge(rt);
		return;
	}
	if(!(rt == el || rt->v < l || rt->v > r))
		merge2(rt->d);
	if (rt->lch && l <= rt->lch->r)
		qry(l, r, el, rt->lch);
	if (rt->rch && r >= rt->rch->l)
		qry(l, r, el, rt->rch);
}
node *gl(int l, int r, node *rt = root)
{
	if (!rt)
		return 0;
	if (l <= rt->l && r >= rt->r)
		return rt->mn;
	if (l > rt->r || r < rt->l)
		return 0;
	node *ret = ((l <= rt->v && r >= rt->v) ? rt : 0);
	if (rt->lch && l <= rt->lch->r)
	{
		node *t = gl(l, r, rt->lch);
		if ((!ret) || (t && t->d < ret->d))
			ret = t;
	}
	if (rt->rch && r >= rt->rch->l)
	{
		node *t = gl(l, r, rt->rch);
		if ((!ret) || (t && t->d < ret->d))
			ret = t;
	}
	return ret;
}

ui v[101010], d[101010];
ui fc[101010];
int main()
{
//	freopen("melancholy.in", "r", stdin);
//	freopen("melancholy.out", "w", stdout);
	int n = g(), m = g();
	fc[1] = 1;
	for (int i = 2; i < 7; i++)
		fc[i] = fc[i - 1] * i;
	for (int i = 0; i < n; i++)
		v[i] = g();
	for (int i = 0; i < n; i++)
		d[i] = g();
	for (int i = 0; i < n; i++)
		ins(v[i], d[i]);
	for (int i = 0; i < m; i++)
	{
		int a = g(), b = g(), c = g();
		ans = node(0, 0);
		qry(a, b, gl(a, b));
		printf("%u\n", fc[c] * ans.t[c]);
	}
	return 0;
}

