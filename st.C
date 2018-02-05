#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
struct node
{
	int v, d, s, to;
	node *r, *l;
	void upd()
	{
		d = r ? r->d + 1 : 0;
		if (r)
		{
			r->v += s;
			r->s += s;
		}
		if (l)
		{
			l->v += s;
			l->s += s;
		}
		s = 0;
	}
	int rd()
	{
		return r ? r->d : -1;
	}
	int ld()
	{
		return l ? l->d : -1;
	}
	node(int vl, int t):to(t), v(vl), d(0), r(0), l(0), s(0){}
};
node *merge(node *a, node *b)
{
	if (!a)
		return b;
	if (!b)
		return a;
	a->upd();
	b->upd();
	if (a->v > b->v)
		swap(a, b);
	a->r = merge(a->r, b);
	a->upd();
	if (a->rd() > a->ld())
		swap(a->r, a->l);
	return a;
}
void del(node *&rt)
{
	if (!rt)
		return;
	rt->upd();
	rt = merge(rt->l, rt->r);
}
void ins(node *&rt, int a, int t)
{
	rt = merge(rt, new node(a, t));
}
void pls(node *rt, int a)
{
	if (!rt)
		return;
	rt->v += a;
	rt->s += a;
}
struct e
{
	int to, nx, tm;
	e(){}
	e(int t, int n, int m):to(t), nx(n), tm(m){}
}es[404040], fs[101010];
int hd[101010], ne, nf, sd[101010];
int dis[101010];
int anc[101010][21];
int ans[101010];
int dep[101010];
bool in[101010];
node *ls[101010];
int tn[101010], nt;
void dfs(int a)
{
	tn[nt] = a;
	for (int i = 0; nt - (1 << i) >= 0; i++)
		anc[a][i] = tn[nt - (1 << i)];
	dep[a] = ++nt;
	for (int i = sd[a]; i != -1; i = fs[i].nx)
		dfs(fs[i].to);
	nt--;
}
int lca(int a, int b)
{
	if (dep[a] > dep[b])
		swap(a, b);
	int t = dep[b] - dep[a];
	for (int i = 0; i < 21; i++)
		if (t & (1 << i))
			b = anc[b][i];
	if (a == b)
		return a;
	for (int i = 20; i >= 0; i--)
		if (anc[b][i] && anc[b][i] != anc[a][i])
		{
			b = anc[b][i];
			a = anc[a][i];
		}
	return anc[a][0];
}
void ae(int a, int b, int t)
{
	es[ne] = e(b, hd[a], t);
	hd[a] = ne++;
	es[ne] = e(a, hd[b], t);
	hd[b] = ne++;
}
int tw(node *a)
{
	return a ? a->to : 0;
}
node *dfs2(int nd)
{
	node *nw = 0;
	for (int i = sd[nd]; i != -1; i = fs[i].nx)
	{
		node *t = dfs2(fs[i].to);
		pls(t, fs[i].tm);
		nw = merge(nw, t);
	}
	nw = merge(nw, ls[nd]);
	if (nd == 1)
		return 0;
	while (nw && lca(tw(nw), nd) == nd)
	{
		del(nw);
	}
	if (nw)
		ans[nd] = nw->v;
	else
		ans[nd] = -1;
	return nw;
}
struct pt
{
	int n, v, fr, ee;
	pt(int nn, int vv, int f, int e):n(nn), v(vv), fr(f), ee(e){}
	bool operator<(const pt a)const
	{
		return v > a.v;
	}
};
int ff[101010];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	memset(hd, -1, sizeof(hd));
	memset(sd, -1, sizeof(sd));
	for (int i = 0; i < m; i++)
	{
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t);
		ae(a, b, t);
	}
	priority_queue<pt> q;
	q.push(pt(1, 0, 0, 0));
	while (!q.empty())
	{
		int nw = q.top().n;
		int d = q.top().v;
		int fr = q.top().fr;
		int ee = q.top().ee;
		q.pop();
		if (in[nw])
			continue;
		in[nw] = 1;
		dis[nw] = d;
		fs[nf] = e(nw, sd[fr], ee);
		sd[fr] = nf++;
		ff[nw] = fr;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
		{
			if (!in[es[i].to])
				q.push(pt(es[i].to, es[i].tm + d, nw, es[i].tm));
		}
	}
	for (int i = 2; i <= n; i++)
		for (int j = hd[i]; j != -1; j = es[j].nx)
			if (es[j].to != ff[i])
				ins(ls[i], es[j].tm + dis[es[j].to], es[j].to);
	dfs(1);
	dfs2(1);
	for (int i = 2; i <= n; i++)
		printf("%d\n", ans[i]);
	return 0;
}
