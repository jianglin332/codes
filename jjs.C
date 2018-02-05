#include <cstdio>
int n, m;
struct node
{
	int l, r;
	int minn, p;
	node *lch, *rch;
	node(){}
	node(int _l, int _r)
	{
		r = _r;
		l = _l;
		minn = 0;
		p = 0;
		lch = rch = 0;
	}
} *root;
inline void makeTree(node *&a, int l, int r)
{
	a = new node(l, r);
	if (l == r)
		return;
	makeTree(a->lch, l, ((l + r) >> 1));
	makeTree(a->rch, ((l + r) >> 1) + 1, r);
}
inline void down(node *nd)
{
	int t = nd->p;
	nd->p = 0;
	nd->lch->minn += t;
	nd->rch->minn += t;
	nd->lch->p += t;
	nd->rch->p += t;
}
inline void insert(int a, int b, node *nd = root)
{
	if (nd->r == nd->l)
	{
		nd->minn = b;
		return;
	}
	if (a <= nd->lch->r)
		insert(a, b, nd->lch);
	else
		insert(a, b, nd->rch);
	nd->minn = nd->lch->minn > nd->rch->minn ? nd->rch->minn : nd->lch->minn;
}
int l, r;
inline bool p1(int d, node *nd = root)
{
	if (l <= nd->l && r >= nd->r)
	{
		nd->minn -= d;
		nd->p -= d;
		return nd->minn < 0;
	}
	down(nd);
	bool flg = 0;
	int mid = ((nd->l + nd->r) >> 1);
	if (l <= mid)
		flg |= p1(d, nd->lch);
	if (r > mid && !flg)
		flg |= p1(d, nd->rch);
	nd->minn = nd->lch->minn > nd->rch->minn ? nd->rch->minn : nd->lch->minn;
	return flg;
}
int main()
{
	scanf("%d%d", &n, &m);
	int tmp;
	makeTree(root, 1, n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &tmp);
		insert(i, tmp);
	}
	for (int i = 1; i <= m; i++)
	{
		int a;
		scanf("%d%d%d", &a, &l, &r);
		if (p1(a))
		{
			printf("-1\n%d", i);
			return 0;
		}
	}
	printf("0");
	return 0;
}
