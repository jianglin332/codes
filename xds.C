#include <iostream>
#include <string.h>
int n, m;
const int mo = 10301;
struct mt
{
	unsigned int v[2][2];
	mt(){memset(v, 0, sizeof(v));}
	mt(int a, int b, int c, int d)
	{
		v[0][0] = a;
		v[0][1] = b;
		v[1][0] = c;
		v[1][1] = d;
	}
	mt operator*(mt &a)
	{
		mt ans;
		ans.v[0][0] = v[0][0] * a.v[0][0] + v[0][1] * a.v[1][0];
		ans.v[0][1] = v[0][0] * a.v[0][1] + v[0][1] * a.v[1][1];
		ans.v[1][0] = v[1][0] * a.v[0][0] + v[1][1] * a.v[1][0];
		ans.v[1][1] = v[1][0] * a.v[0][1] + v[1][1] * a.v[1][1];
		return ans;
	}
}ca(1, 1, 0, 1), cb(1, 0, 1, 1);
struct node
{
	unsigned int l, r;
	unsigned int ab, aa, bb;
	mt t;
	node *lch, *rch;
	node(){}
	node(int _l, int _r, int a)
	{
		r = _r;
		l = _l;
		ab = aa = bb = a;
		lch = rch = 0;
		t.v[0][0] = t.v[1][1] = 1;
	}
} *root;
void makeTree(node *&a, int l, int r)
{
	if (l > r)
		return;
	a = new node(l, r, 0);
	if (l == r)
		return;
	makeTree(a->lch, l, ((l + r) >> 1));
	makeTree(a->rch, ((l + r) >> 1) + 1, r);
}
void down(node *nd)
{
	unsigned int ab = nd->rch->ab, aa = nd->rch->aa, bb = nd->rch->bb;
	unsigned int (*v)[2] = nd->t.v;
	nd->rch->ab = (v[0][0] * v[1][0] * aa + v[0][1] * v[1][1] * bb + (v[0][1] * v[1][0] + v[1][1] * v[0][0]) * ab) % mo;
	nd->rch->aa = (v[0][0] * v[0][0] * aa + v[0][1] * v[0][1] * bb + 2 * v[0][0] * v[0][1] * ab) % mo;
	nd->rch->bb = (v[1][0] * v[1][0] * aa + v[1][1] * v[1][1] * bb + 2 * v[1][0] * v[1][1] * ab) % mo;
	nd->rch->t = nd->t * nd->rch->t;
	ab = nd->lch->ab, aa = nd->lch->aa, bb = nd->lch->bb;
	nd->lch->ab = (v[0][0] * v[1][0] * aa + v[0][1] * v[1][1] * bb + (v[0][1] * v[1][0] + v[1][1] * v[0][0]) * ab) % mo;
	nd->lch->aa = (v[0][0] * v[0][0] * aa + v[0][1] * v[0][1] * bb + 2 * v[0][0] * v[0][1] * ab) % mo;
	nd->lch->bb = (v[1][0] * v[1][0] * aa + v[1][1] * v[1][1] * bb + 2 * v[1][0] * v[1][1] * ab) % mo;
	nd->lch->t = nd->t * nd->lch->t;
	nd->t.v[0][0] = nd->t.v[1][1] = 1;
	nd->t.v[0][1] = nd->t.v[1][0] = 0;
}
void upd(node *nd)
{
	nd->ab = (nd->rch->ab + nd->lch->ab) % mo;
	nd->aa = (nd->rch->aa + nd->lch->aa) % mo;
	nd->bb = (nd->rch->bb + nd->lch->bb) % mo;
}
void insert(int a, int b, int c, node *nd = root)
{
	if (nd->r == nd->l)
	{
		nd->aa = ((a % mo) * (a % mo)) % mo;
		nd->bb = ((b % mo) * (b % mo)) % mo;
		nd->ab = ((a % mo) * (b % mo)) % mo;
		return;
	}
	if (c <= nd->lch->r)
		insert(a, b, c, nd->lch);
	else
		insert(a, b, c, nd->rch);
	upd(nd);
}
void p1(int l, int r, node*nd = root)
{
	if (l == nd->l && r == nd->r)
	{
		nd->aa = (nd->aa + nd->bb + nd->ab * 2) % mo;
		nd->ab = (nd->ab + nd->bb) % mo;
		nd->t = nd->t * ca;
		return;
	}
	down(nd);
	if (l < nd->rch->l)
		p1(l, nd->lch->r > r ? r : nd->lch->r, nd->lch);
	if (r > nd->lch->r)
		p1(nd->rch->l > l ? nd->rch->l : l, r, nd->rch);
	upd(nd);
}
void p2(int l, int r, node*nd = root)
{
	if (l == nd->l && r == nd->r)
	{
		nd->bb = (nd->aa + nd->bb + nd->ab * 2) % mo;
		nd->ab = (nd->ab + nd->aa) % mo;
		nd->t = nd->t * cb;
		return;
	}
	down(nd);
	if (l < nd->rch->l)
		p2(l, nd->lch->r > r ? r : nd->lch->r, nd->lch);
	if (r > nd->lch->r)
		p2(nd->rch->l > l ? nd->rch->l : l, r, nd->rch);
	upd(nd);
}
unsigned int tt;
void ps(int l, int r, node *nd = root)
{
	if (l == nd->l && r == nd->r)
	{
		tt = (nd->ab + tt) % mo;
		return;
	}
	down(nd);
	if (l < nd->rch->l)
		ps(l, nd->lch->r > r ? r : nd->lch->r, nd->lch);
	if (r > nd->lch->r)
		ps(nd->rch->l > l ? nd->rch->l : l, r, nd->rch);
}
int main()
{
	std::cin.sync_with_stdio(0);
	std::cin>>n>>m;
	int tmp, tmm;
	makeTree(root, 1, n);
	for (int i = 1; i <= n; i++)
	{
		std::cin>>tmp>>tmm;
		insert(tmp, tmm, i);
	}
	for (int i = 0; i < m; i++)
	{
		std::cin>>tmp;
		if (tmp == 1)
		{
			std::cin>>tmp>>tmm;
			p1(tmp, tmm);
		}
		if (tmp == 2)
		{
			std::cin>>tmp>>tmm;
			p2(tmp, tmm);
		}
		else if (tmp == 3)
		{
			std::cin>>tmp>>tmm;
			tt = 0;
			ps(tmp, tmm);
			std::cout<<tt<<std::endl;
		}
	}
}
