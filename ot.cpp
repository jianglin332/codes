#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
struct node
{
	int l, r;
	node *lch, *rch;
	ll s;
	ll la, lb;
	node *plus(ll a, ll b)
	{
		node *ret = new node(this);
		ret->s += a * (r - l + 1) + b * (r - l) * (r - l + 1) / 2;
		ret->la += a, ret->lb += b;
		return ret;
	}
	void down()
	{
		if (!la && !lb)
			return;
		lch = lch->plus(la, lb);
		rch = rch->plus(la + lb * (lch->r - l + 1), lb);
		la = lb = 0;
	}
	void upd()
	{
		s = lch->s + rch->s;
	}
	node(int ll, int rr)
	{
		l = ll, r = rr;
		s = la = lb = 0;
		int mid = (l + r) / 2;
		if (l != r)
			lch = new node(l, mid), rch = new node(mid + 1, r);
	}
	node(node *a)
	{
		*this = *a;
	}
} *rs[101010], *nw;
int nr;
node *add(int l, int r, ll a, ll b, node *n)
{
	if (l <= n->l && n->r <= r)
		return n->plus(a + (n->l - l) * b, b);
	n->down();
	node *nw = new node(n);
	if (nw->lch->r >= l)
		nw->lch = add(l, r, a, b, nw->lch);
	if (nw->rch->l <= r)
		nw->rch = add(l, r, a, b, nw->rch);
	nw->upd();
	return nw;
}
ll qr(int l, int r, node *n = nw)
{
	if (l <= n->l && n->r <= r)
		return n->s;
	n->down();
	ll rt = 0;
	if (n->lch->r >= l)
		rt += qr(l, r, n->lch);
	if (n->rch->l <= r)
		rt += qr(l, r, n->rch);
	return rt;
}
struct ed
{
	int to, nx;
}es[202020];
int hd[101010], ne;
void ae(int f, int t)
{
	es[ne].to = t;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
int size[101010], hv[101010], dfn[101010], tp[101010], f[101010][20], h[101010], nfn;
int df1(int a, int fa)
{
	for (int i = 0; i < 18; i++)
	{
		if (!f[a][i])
			break;
		f[a][i + 1] = f[f[a][i]][i];
	}
	size[a] = 1;
	h[a] = h[fa] + 1;
	int mx = 0;
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa)
		{
			f[es[i].to][0] = a;
			int s = df1(es[i].to, a);
			if (s > mx)
				hv[a] = es[i].to, mx = s;
			size[a] += s;
		}
	return size[a];
}
void df2(int a, int fa)
{
	dfn[a] = ++nfn;
	if (hv[fa] == a)
		tp[a] = tp[fa];
	else
		tp[a] = a;
	if (!hv[a])
		return;
	df2(hv[a], a);
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa && es[i].to != hv[a])
			df2(es[i].to, a);
}
int lca(int a, int b)
{
	if (h[a] < h[b])
		swap(a, b);
	for (int i = 17; i >= 0; i--)
		if (h[a] - (1 << i) >= h[b])
			a = f[a][i];
	if (a == b)
		return a;
	for (int i = 17; i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
node *Add(int a, int b, int c, int d, node *e)
{
	return add(dfn[a], dfn[b], c, d, e);
}
node *c(int x, int y, int a, int b)
{
	node *r = nw;
	int fa = lca(x, y);
	int l = h[x] + h[y] - h[fa] - h[fa] + 1;
	int la = a, ra = a + (l - 1) * b;
	while (1)
	{
		if (tp[x] == tp[y])
		{
			if (h[x] < h[y])
				r = Add(x, y, la, b, r);
			else
				r = Add(y, x, ra, -b, r);
			break;
		}
		else if (h[tp[x]] > h[tp[y]])
		{
			r = Add(tp[x], x, la + (h[x] - h[tp[x]]) * b, -b, r);
			la += (h[x] - h[tp[x]] + 1) * b;
			x = f[tp[x]][0];
		}
		else
		{
			r = Add(tp[y], y, ra - (h[y] - h[tp[y]]) * b, b, r);
			ra -= (h[y] - h[tp[y]] + 1) * b;
			y = f[tp[y]][0];
		}
	}
	return r;
}
ll q(int x, int y)
{
	ll ret = 0;
	while (1)
	{
		if (tp[x] == tp[y])
		{
			ret += qr(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]));
			break;
		}
		else if (h[tp[x]] > h[tp[y]])
		{
			ret += qr(dfn[tp[x]], dfn[x]);
			x = f[tp[x]][0];
		}
		else
		{
			ret += qr(dfn[tp[y]], dfn[y]);
			y = f[tp[y]][0];
		}
	}
	return ret;
}
char tm[5];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	memset(hd, -1, sizeof(hd));
	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ae(a, b), ae(b, a);
	}
	df1(1, 0);
	df2(1, 0);
	nw = rs[0] = new node(1, nfn);
	long long la = 0;
	for (int i = 0; i < m; i++)
	{
		scanf("%s", tm);
		if (tm[0] == 'c')
		{
			int x, y, a, b;
			scanf("%d%d%d%d", &x, &y, &a, &b);
			x = (x + la) % n + 1;
			y = (y + la) % n + 1;
			nw = rs[++nr] = c(x, y, a, b);
		}
		else if (tm[0] == 'q')
		{
			int x, y;
			scanf("%d%d", &x, &y);
			x = (x + la) % n + 1;
			y = (y + la) % n + 1;
			printf("%lld\n", la = q(x, y));
		}
		else
		{
			int x;
			scanf("%d", &x);
			x = (x + la) % (nr + 1);
			nw = rs[x];
		}
	}
	return 0;
}
