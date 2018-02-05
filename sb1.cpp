#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[101010], b[101010];
long long s[101010];
int inf = 2e9 + 7;
struct node
{
	int l, r;
	node *lch, *rch;
	int mc, se, nn;
	long long sa, sc;
	int lp, lm;
	void plus(int pl)
	{
		sa += (r - l + 1ll) * pl, sc += (r - l + 1ll) * pl, mc += pl, se += pl, lp += pl;
		if (lm != inf)
			lm += pl;
	}
	void max(int t)
	{
		if (mc >= t)
			return;
		if (l == r)
		{
			mc = sc = t;
			return;
		}
		if (se > t)
		{
			sc += (t - mc + 0ll) * nn;
			mc = t, lm = t;
		}
		else
		{
			down();
			lch->max(t), rch->max(t);
			upd();
		}
	}
	void down()
	{
		if (!lch)
			return;
		if (lp != 0)
			lch->plus(lp), rch->plus(lp), lp = 0;
		if (lm != inf)
			lch->max(lm), rch->max(lm), lm = inf;
	}
	void upd()
	{
		if (!lch)
			return;
		sa = lch->sa + rch->sa;
		sc = lch->sc + rch->sc;
		mc = lch->mc;
		nn = lch->nn;
		se = lch->se;
		if (rch->mc < mc)
			se = mc, mc = rch->mc, nn = rch->nn;
		else if (rch->mc == mc)
			nn += rch->nn;
		else if (rch->mc < se)
			se = rch->mc;
		if (rch->se < se)
			se = rch->se;
	}
	node(int l, int r):l(l), r(r)
	{
		lp = 0, lm = inf;
		if (l == r)
			sa = a[l], lch = rch = 0, mc = sc = 0, se = inf, nn = 1;
		else
		{
			lch = new node(l, (l + r) / 2);
			rch = new node((l + r) / 2 + 1, r);
			upd();
		}
	}
	long long qry(int ll, int rr)
	{
		if (ll <= l && r <= rr)
			return sa - sc;
		down();
		long long rt = 0;
		if (ll <= lch->r)
			rt += lch->qry(ll, rr);
		if (rr >= rch->l)
			rt += rch->qry(ll, rr);
		return rt;
	}
	void pls(int ll, int rr, int c)
	{
		down();
		if (ll <= l && r <= rr)
			plus(c), max(0);
		else
		{
			if (ll <= lch->r)
				lch->pls(ll, rr, c);
			if (rr >= rch->l)
				rch->pls(ll, rr, c);
			upd();
		}
	}
} *root;
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	if (n < 10101)
	{
		for (int i = 1; i <= n; i++)
			b[i] = a[i];
		for (int i = 0; i < m; i++)
		{
			int t, l, r, c;
			scanf("%d%d%d", &t, &l, &r);
			if (t == 1)
			{
				scanf("%d", &c);
				for (int j = l; j <= r; j++)
					b[j] = min(b[j], a[j] += c);
			}
			if (t == 2)
			{
				scanf("%d", &c);
				for (int j = l; j <= r; j++)
					a[j] = max(a[j], c);
			}
			if (t == 3)
			{
				long long f = 0;
				for (int j = l; j <= r; j++)
					f += b[j];
				printf("%lld\n", f);
			}
		}
	}
	else
	{
		root = new node(1, n);
//		for (int i = 1; i <= n; i++)
//			s[i] = s[i - 1] + a[i];
		for (int i = 0; i < m; i++)
		{
			int t, l, r, c;
			scanf("%d%d%d", &t, &l, &r);
			if (t == 3)
				printf("%lld\n", root->qry(l, r));
			else
			{
				scanf("%d", &c);
				root->pls(l, r, c);
			}
		}
	}
	return 0;
}
