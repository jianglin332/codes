#include <cstdio>
#include <cstdlib>
struct node
{
	int h, v;
	long long s, t;
	node *rch, *lch;
	node(int vi, long long ti)
	{
		s = ti;
		rch = lch = 0;
		h = rand();
		v = vi;
		t = ti;
	}
} *root = 0;
long long gett(node *a)
{
	if (!a)
		return 0;
	return a->t;
}
void upd(node *a)
{
	a->t = gett(a->rch) + gett(a->lch) + a->s;
}
void insert(node *&root, int v, long long s)
{
	if (!root)
	{
		root = new node(v, s);
	}
	else if (root->v <= v)
	{
		insert(root->rch, v, s);
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
		insert(root->lch, v, s);
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
long long getr(node *a, int v)
{
	if (!a)
		return 0;
	if (a->v > v)
		return getr(a->lch, v);
	if (a->v == v)
		return gett(a->lch);
	if (a->v < v)
		return getr(a->rch, v) + gett(a->lch) + a->s;
}
int main()
{
	int n, v;
	char ch;
	scanf("%d", &n);
	node *rt = 0;
	long long ans = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &v);
		ans += getr(rt, v);
		long long t = getr(root, v);
		if (t)
			insert(rt, v, t);
		insert(root, v, 1);
	}
	printf("%I64d", ans);
	return 0;
}
