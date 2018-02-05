#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct ed
{
	int to, nx, len;
}es[20202];
int lb[20202], rk[20202], nl;
int heavy[10101];
int d[10101];
int hd[10101], ne;
int top[10101];
int ef[10101];
int ft[10101];
struct node
{
	int l, r, s;
	node *lch, *rch;
	void upd()
	{
		if (lch)
			s = max(lch->s, rch->s);
	}
}*root;
void mkt(int l, int r, node *&nd = root)
{
	nd = new node;
	if (l == r)
	{
		nd->r = nd->l = l;
		nd->lch = nd->rch = 0;
		nd->s = es[rk[l]].len;
	}
	else
	{
		nd->r = r;
		nd->l = l;
		mkt(l, (l + r) / 2, nd->lch);
		mkt((l + r) / 2 + 1, r, nd->rch);
		nd->upd();
	}
}
void chg(int a, int b, node *nd = root)
{
	if (nd->l == nd->r)
	{
		nd->s = b;
		return;
	}
	if (nd->lch->r >= a)
		chg(a, b, nd->lch);
	else
		chg(a, b, nd->rch);
	nd->upd();
}
int qry(int a, int b, node *nd = root)
{
	if (nd->l >= a && nd->r <= b)
		return nd->s;
	int ret = 0;
	if (nd->lch->r >= a)
		ret = max(qry(a, b, nd->lch), ret);
	if (nd->rch->l <= b)
		ret = max(qry(a, b, nd->rch), ret);
	return ret;
}
void ae(int fr, int to, int l)
{
	es[ne].to = to;
	es[ne].len = l;
	es[ne].nx = hd[fr];
	hd[fr] = ne++;
}
int dfs(int nd, int fa)
{
	int ret = 1, mx = 0;
	for (int i = hd[nd]; i != -1; i = es[i].nx)
		if (es[i].to != fa)
		{
			ft[es[i].to] = nd;
			ef[es[i].to] = i;
			d[es[i].to] = d[nd] + 1;
			int t = dfs(es[i].to, nd);
			if (t > mx)
			{
				heavy[nd] = i;
				mx = t;
			}
			ret += t;
		}
	return ret;
}
void dfs2(int nd, int fr)
{
	if (heavy[nd] == -1)
		return;
	int hv = heavy[nd];
	rk[nl] = hv;
	lb[hv >> 1] = nl++;
	top[es[hv].to] = top[nd];
	dfs2(es[hv].to, nd);
	for (int i = hd[nd]; i != -1; i = es[i].nx)
		if (i != hv && es[i].to != fr)
		{
			rk[nl] = i;
			lb[i >> 1] = nl++;
			top[es[i].to] = es[i].to;
			dfs2(es[i].to, nd);
		}
}
char bf[11];
#define ms(x) memset(x, 0, sizeof(x))
void go()
{
	ms(lb), ms(rk);
	ms(d);
	ms(es);
	ms(top);
	ms(ef);
	ms(ft);
	root = 0;
	ne = 0;
	nl = 0;
	memset(hd, -1, sizeof(hd));
	memset(heavy, -1, sizeof(heavy));
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		ae(a, b, c);
		ae(b, a, c);
	}
	dfs(1, 0);
	top[1] = 1;
	dfs2(1, 0);
	mkt(0, nl - 1);
	while (1)
	{
		scanf("%s", bf);
		if (bf[0] == 'D')
			break;
		if (bf[0] == 'C')
		{
			int a, b;
			scanf("%d%d", &a, &b);
			chg(lb[a - 1], b);
		}
		if (bf[0] == 'Q')
		{
			int a, b;
			scanf("%d%d", &a, &b);
			int f1 = top[a], f2 = top[b];
			int ans = 0;
			while (f1 != f2)
			{
				if (d[f1] < d[f2])
				{
					swap(f1, f2);
					swap(a, b);
				}
				ans = max(qry(lb[ef[f1] >> 1], lb[ef[a] >> 1]), ans);
				a = ft[f1];
			f1 = top[a];
			}
			if (d[a] > d[b])
				swap(a, b);
			if (a != b)
				ans = max(qry(lb[heavy[a] >> 1], lb[ef[b] >> 1]), ans);
			printf("%d\n", ans);
		}
	}
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		go();
}
