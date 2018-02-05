#include <stdio.h>
#include <algorithm>
using namespace std;
int b[151515], a[151515], n, len, h;
struct node
{
	int l, r, mn, lazy;
	node *lch, *rch;
	void down()
	{
		if (!lch)
			return;
		lch->mn += lazy;
		rch->mn += lazy;
		lch->lazy += lazy;
		rch->lazy += lazy;
		lazy = 0;
	}
	void up()
	{
		if (!lch)
			return;
		mn = min(lch->mn, rch->mn);
	}
} *root;
void plus(int v, int to, node *rt = root)
{
	if (to >= rt->r)
	{
		rt->mn += v;
		rt->lazy += v;
		return;
	}
	rt->down();
	if (rt->lch->r < to)
		plus(v, to, rt->rch);
	plus(v, to, rt->lch);
	rt->up();
}
void mkt(int l, int r, node *&rt = root)
{
	rt = new node;
	rt->l = l;
	rt->r = r;
	rt->lazy = 0;
	if (l == r)
	{
		rt->mn = -len + l;
		rt->lch = rt->rch = 0;
		return;
	}
	mkt(l, (l + r) / 2, rt->lch);
	mkt((l + r) / 2 + 1, r, rt->rch);
	rt->up();
}
int pos(int v)
{
	int st = 0, ed = len;
	while (st + 1 < ed)
	{
		int mid = (st + ed) / 2;
		if (b[mid] <= v)
			st = mid;
		else
			ed = mid;
	}
	return st;
}
int main()
{
	scanf("%d%d%d", &n, &len, &h);
	for (int i = 0; i < len; i++)
	{
		scanf("%d", b + i);
		b[i] = h - b[i];
	}
	sort(b, b + len);
	mkt(0, len - 1);
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", a + i);
		if (a[i] >= b[0])
			plus(1, pos(a[i]));
		if (i >= len && a[i - len] >= b[0])
			plus(-1, pos(a[i - len]));
		if (i >= len - 1 && root->mn >= 0)
			ans++;
	}
	printf("%d", ans);
}
