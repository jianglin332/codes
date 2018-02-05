#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct seg
{
	double k, b;
	int n;
	double gy(double x)
	{
		return k * x + b;
	}
	seg(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0, int n = 0):n(n)
	{
		if (x1 == x2)
			k = 0, b = max(y1, y2);
		else
			k = (y1 - y2) / (x1 - x2), b = y1 - k *x1; 
	}
};
struct node
{
	int l, r;
	node *lch, *rch;
	seg s;
	node(int l, int r):l(l), r(r)
	{
		if (l == r)
			lch = rch = 0;
		else
			lch = new node(l, (l + r) / 2), rch = new node((l + r) / 2 + 1, r);
	}
} *root;
int sig(double x)
{
	return fabs(x) < 1e-8 ? 0 : (x > 0 ? 1 : -1);
}
void add(seg s, int l, int r, node *nd = root)
{
	if (l <= nd->l && nd->r <= r)
	{
		l = nd->l, r = nd->r;
		int a = sig(nd->s.gy(l) - s.gy(l)), b = sig(nd->s.gy(r) - s.gy(r));
		if (a < 0 && b < 0)
		{
			nd->s = s;
			return;
		}
		if (a >= 0 && b >= 0)
			return;
		if (a == b)
			return;
	}
	if (l <= nd->lch->r)
		add(s, l, r, nd->lch);
	if (r >= nd->rch->l)
		add(s, l, r, nd->rch);
}
seg &qry(int x, node *nd = root)
{
	if (nd->l == nd->r)
		return nd->s;
	if (x <= nd->lch->r)
	{
		seg &a = qry(x, nd->lch);
		int f = sig(nd->s.gy(x) - a.gy(x));
		if (f > 0)
			return nd->s;
		else if (f < 0)
			return a;
		else if (a.n < nd->s.n)
			return a;
		else
			return nd->s;
	}
	else
	{
		seg &a = qry(x, nd->rch);
		int f = sig(nd->s.gy(x) - a.gy(x));
		if (f > 0)
			return nd->s;
		else if (f < 0)
			return a;
		else if (a.n < nd->s.n)
			return a;
		else
			return nd->s;
	}
}
int main()
{
	freopen("segment.in", "r", stdin);
	freopen("segment.out", "w", stdout);
	int n;
	scanf("%d", &n);
	root = new node(1, 39989);
	int la = 0;
	int nl = 0;
	for (int i = 0; i < n; i++)
	{
		int t;
		scanf("%d", &t);
		if (t == 1)
		{
			nl++;
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			x1 = (x1 + la - 1) % 39989 + 1;
			x2 = (x2 + la - 1) % 39989 + 1;
			y1 = (y1 + la - 1) % 1000000000 + 1;
			y2 = (y2 + la - 1) % 1000000000 + 1;
			if (x1 > x2)
				swap(x1, x2), swap(y1, y2);
			add(seg(x1, y1, x2, y2, nl), x1, x2);
		}
		else
		{
			int k;
			scanf("%d", &k);
			k = (k + la - 1) % 39989 + 1;
			int ans = qry(k).n;
			printf("%d\n", ans);
			la = ans;
		}
	}
}
