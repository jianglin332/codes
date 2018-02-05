#include <cstdio>
#include <cstdlib>
struct node
{
	int h, v, t;
	node *rch, *lch;
	node(int vi)
	{
		rch = lch = 0;
		h = rand();
		v = vi;
		t = 1;
	}
} *root = 0;
int gett(node *a)
{
	if (!a)
		return 0;
	return a->t;
}
void upd(node *a)
{
	a->t = gett(a->rch) + gett(a->lch) + 1;
}
void insert(node *&root, int v)
{
	if (!root)
	{
		root = new node(v);
	}
	else if (root->v <= v)
	{
		insert(root->rch, v);
		upd(root);
		if (root->h > root->rch->h)
		{
			node *a = root->rch;
			root->rch = a->lch;
			a->lch = root;
			root = a;
			upd(root->lch);
			upd(root);
		}
	}
	else
	{
		insert(root->lch, v);
		upd(root);
		if (root->h > root->lch->h)
		{
			node *a = root->lch;
			root->lch = a->rch;
			a->rch = root;
			root = a;
			upd(root->rch);
			upd(root);
		}
	}
}
int getr(node *a, int v)
{
	if (!a)
		return -1;
	if (a->v > v)
		return getr(a->lch, v);
	if (a->v == v)
	{
		int n = getr(a->lch, v);
		if (n == -1)
			return gett(a->lch) + 1;
		return n;
	}
	if (a->v < v)
	{
		int n = getr(a->rch, v);
		if (n == -1)
			return -1;
		return n + gett(a->lch) + 1;
	}
	return -1;
}
int getk(node *a, int d)
{
	if (!a)
		return -1;
	int n = gett(a->lch) + 1;
	if (n == d)
	{
		return a->v;
	}
	if (n < d)
	{
		return getk(a->rch, d - n);
	}
	return getk(a->lch, d);
}
int main()
{
	int n, v;
	char ch;
	scanf("%d", &n);
	for (; n; n--)
	{
		scanf("\n%c %d", &ch, &v);
		if (ch == 'I')
			insert(root, v);
		else if (ch == 'R')
			printf("%d\n", getr(root, v));
		else if (ch == 'K')
			printf("%d\n", getk(root, v));
	}
	return 0;
}