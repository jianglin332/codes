#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <algorithm>
using namespace std;
struct qr
{
	long long r1, r2;
	int ans, n;
}qs[101010];
bool cmp1(const qr &a, const qr &b)
{
	return a.r1 < b.r1;
}
bool cmp2(const qr &a, const qr &b)
{
	return a.n < b.n;
}
int g()
{
	int r = 0;
	char c;
	bool flg = 0;
	while (!isdigit(c = getchar()) && c != '-');
	if (c == '-')
		flg = 1;
	else
		r = c - '0';
	while (isdigit(c = getchar()))
		r = r * 10 + c - '0';
	return r * (flg ? -1 : 1);
}
struct point
{
	long long da, db;
}ps[202020];
bool cmpp(const point &a, const point &b)
{
	return a.da < b.da;
}
struct node
{
	node *lch, *rch;
	long long v;
	int d, size;
	node(long long vv)
	{
		d = rand();
		v = vv;
		lch = rch = 0;
		size = 1;
	}
	void upd()
	{
		size = (lch ? lch->size : 0) + (rch ? rch->size : 0) + 1;
	}
};
struct treap
{
	node *root;
	treap():root(0){}
	void alt(node *&rt)
	{
		if (rt->lch && rt->lch->d < rt->d)
		{
			node *t = rt->lch;
			rt->lch = t->rch;
			t->rch = rt;
			rt = t;
			t->rch->upd();
			t->upd();
		}
		if (rt->rch && rt->rch->d < rt->d)
		{
			node *t = rt->rch;
			rt->rch = t->lch;
			t->lch = rt;
			rt = t;
			t->lch->upd();
			t->upd();
		}
	}
	void ins(long long v, node *&rt)
	{
		if (!rt)
			rt = new node(v);
		else if (rt->v < v)
		{
			ins(v, rt->rch);
			rt->upd();
		}
		else
		{
			ins(v, rt->lch);
			rt->upd();
		}
		alt(rt);
	}
	int get(long long v, node *rt)
	{
		if (!rt)
			return 0;
		if (v < rt->v)
			return get(v, rt->lch);
		return (rt->lch ? rt->lch->size : 0) + 1 + get(v, rt->rch);
	}
}ta, tb;
int main()
{
	freopen("supply.in", "r", stdin);
	freopen("supply.out", "w", stdout);
	int n = g(), m = g();
	int ax = g(), ay = g(), bx = g(), by = g();
	for (int i = 0; i < n; i++)
	{
		long long x = g(), y = g();
		ps[i].da = (ax - x) * (ax - x) + (ay - y) * (ay - y);
		ps[i].db = (bx - x) * (bx - x) + (by - y) * (by - y);
	}
	sort(ps, ps + n, cmpp);
	for (int i = 0; i < m; i++)
	{
		long long a = g(), b = g();
		qs[i].r1 = a * a;
		qs[i].r2 = b * b;
		qs[i].n = i;
	}
	for (int i = 0; i < n; i++)
		tb.ins(ps[i].db, tb.root);
	sort(qs, qs + m, cmp1);
	int pnow = 0;
	for (int i = 0; i < m; i++)
	{
		while (pnow < n && ps[pnow].da <= qs[i].r1)
		{
			ta.ins(ps[pnow].db, ta.root);
			pnow++;
		}
		qs[i].ans = pnow + tb.get(qs[i].r2, tb.root) - ta.get(qs[i].r2, ta.root);
	}
	sort(qs, qs + m, cmp2);
	for (int i = 0; i < m; i++)
		printf("%d\n", qs[i].ans);
	return 0;
}
