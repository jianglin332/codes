#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int place[101010], np;
int real[101010];
struct ed
{
	int to, nx;
}es[202020];
int hd[101010], ne;
void ae(int fr, int to)
{
	es[ne].to = to;
	es[ne].nx = hd[fr];
	hd[fr] = ne++;
}
int h[101010];
int heavy[101010];
int father[101010];
int top[101010];
int sz[101010];
int dfs1(int nw)
{
	int mx = 0, ret = 1;
	for (int i = hd[nw]; i != -1; i = es[i].nx)
		if (es[i].to != father[nw])
		{
			int to = es[i].to;
			h[to] = h[nw] + 1;
			father[to] = nw;
			int t = dfs1(to);
			ret += t;
			if (t > mx)
			{
				heavy[nw] = to;
				t = mx;
			}
		}
	sz[nw] = ret;
	return ret;
}
void dfs2(int nw)
{
	if (heavy[nw] == -1)
		return;
	int hv = heavy[nw];
	top[hv] = top[nw];
	place[hv] = np;
	real[np++] = hv;
	dfs2(hv);
	for (int i = hd[nw]; i != -1; i = es[i].nx)
		if (es[i].to != hv && es[i].to != father[nw])
		{
			int to = es[i].to;
			top[to] = to;
			place[to] = np;
			real[np++] = to;
			dfs2(to);
		}
}
struct node
{
	int color[2];
	node *lch, *rch;
	int lazy[2];
	int l, r;
	void init(int ll)
	{
		l = r = ll;
		color[0] = 1;
		color[1] = 0;
		lch = rch = 0;
		lazy[0] = sz[real[ll]] - 1;
		lazy[1] = 0;
	}
	void down()
	{
		if (!lch)
			return;
		lch->lazy[0] += lazy[0];
		rch->lazy[0] += lazy[0];
		lch->lazy[1] += lazy[1];
		rch->lazy[1] += lazy[1];
		lazy[0] = 0;
		lazy[1] = 0;
	}
	void upd()
	{
		if (!lch)
			return;
		color[0] = lch->color[0] + rch->color[0];
		color[1] = lch->color[1] + rch->color[1];
	}
} *root;
node *qry(int t, node *nd = root)
{
	if (nd->r == nd->l)
	{
		return nd;
	}
	nd->down();
	if (t <= nd->lch->r)
		return qry(t, nd->lch);
	else
		return qry(t, nd->rch);
}
void add(int l, int r, int c, int v, node *nd = root)
{
	if (l > nd->r || r < nd->l)
		return;
	if (l <= nd->l && nd->r <= r)
	{
		nd->lazy[c] += v;
		return;
	}
	nd->down();
	if (l <= nd->lch->r)
		add(l, r, c, v, nd->lch);
	if (nd->rch->l <= r)
		add(l, r, c, v, nd->rch);
}
int qc(int l, int r, int c, node *nd = root)
{
	if (l > nd->r || r < nd->l)
		return 0;
	if (l <= nd->l && nd->r <= r)
		return nd->color[c];
	int rt = 0;
	if (l <= nd->lch->r)
		rt += qc(l, r, c, nd->lch);
	if (nd->rch->l <= r)
		rt += qc(l, r, c, nd->rch);
	return rt;
}
void mkt(int l, int r, node *&nd = root)
{
	nd = new node;
	if (l == r)
		nd->init(l);
	else
	{
		nd->l = l;
		nd->r = r;
		mkt(l, (l + r) / 2, nd->lch);
		mkt((l + r) / 2 + 1, r, nd->rch);
		nd->lazy[0] = nd->lazy[1] = 0;
		nd->upd();
	}
}
void chgc(int a, node *nd = root)
{
	if (nd->r == nd->l)
	{
		swap(nd->color[0], nd->color[1]);
		return;
	}
	if (a <= nd->lch->r)
		chgc(a, nd->lch);
	else
		chgc(a, nd->rch);
	nd->upd();
}
int rq(int a, int c, node *nd = root)
{
	if (nd->r == nd->l)
	{
		return nd->lazy[c] + 1;
	}
	nd->down();
	if (a <= nd->lch->r)
		return rq(a, c, nd->lch);
	else
		return rq(a, c, nd->rch);
}
int req(int a)
{
	int f = top[a];
	node *nd = qry(place[a]);
	int color = !nd->color[0];
	while (a != 1)
	{
		if (qc(place[f], place[a], color) != place[a] - place[f] + 1)
			break;
		if (f == 1 || qry(place[father[f]])->color[0] == color)
		{
			return rq(place[f], color);
		}
		a = father[f];
		f = top[a];
	}
	int l = 0, r = place[a] - place[f];
	while (r - l > 1)
	{
		int mid = (l + r) / 2;
		if (qc(place[a] - mid, place[a], color) == mid + 1)
			l = mid;
		else
			r = mid;
	}
	return rq(place[a] - l, color);
}
void chg(int a)
{
	if (a == 1)
	{
		chgc(place[a]);
		return;
	}
	int oa = a;
	int f = top[a];
	node *nd = qry(place[a]);
	int color = !nd->color[0];
	int minus = nd->lazy[color];
	int plus = nd->lazy[!color];
	if (a != 1)
	{
		add(place[father[a]], place[father[a]], !color, plus + 1);
		add(place[father[a]], place[father[a]], color, -minus - 1);
	}
	a = father[a];
	f = top[a];
	int clr = !qry(place[a])->color[0];
	int sgn = clr == color;
	int flg = 1;
	while (a != 1)
	{
		if (qc(place[f], place[a], clr) != h[a] - h[f] + 1)
			break;
		if (h[f] <= h[father[a]])
			add(place[f], place[father[a]], clr, sgn ? (-minus - 1) : plus + 1);
		if (f != 1)
			add(place[father[f]], place[father[f]], clr, sgn ? (-minus - 1) : plus + 1);
		if (f == 1 || qry(place[father[f]])->color[0] == clr)
		{
			flg = 0;
			break;
		}
		a = father[f];
		f = top[a];
	}
	if (flg)
	{
		int l = 0, r = place[a] - place[f];
		while (r - l > 1)
		{
			int mid = (l + r) / 2;
			if (qc(place[a] - mid, place[a], clr) == mid + 1)
				l = mid;
			else
				r = mid;
		}
		if (a != 1)add(place[a] - l - 1, place[a] - 1, clr, sgn ? (-minus - 1) : plus + 1);
	}
	chgc(place[oa]);
}
int main()
{
	int n;
	scanf("%d", &n);
	memset(hd, -1, sizeof(hd));
	memset(heavy, -1, sizeof(heavy));
	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ae(a, b);
		ae(b, a);
	}
	father[1] = 1;
	dfs1(1);
	top[1] = 1;
	real[np] = 1;
	place[1] = np++;
	dfs2(1);
	mkt(0, n - 1);
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if (a == 0)
			printf("%d\n", req(b));
		else
		{
			chg(b);
		}
	}
	return 0;
}
