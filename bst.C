#include <cstdio>
#include <cstdlib>
const int maxn = 1010101;
int in[110000];
struct node
{
	int v, d, siz;
	node *l, *r;
	void upd()
	{
		siz = 1 + (l ? l->siz : 0) + (r ? r->siz : 0);
	}
	int sz()
	{
		return l ? l->siz : 0;
	}
	node(int a)
	{
		l = r = 0;
		v = a;
		siz = 1;
		d = rand();
	}
} *root;
struct pn
{
	node *a, *b;
	pn(node *c, node *d):a(c), b(d){};
};
node *merge(node *a, node *b)
{
	if (!a)
		return b;
	if (!b)
		return a;
	if (a->d < b->d)
	{
		a->r = merge(a->r, b);
		a->upd();
		return a;
	}
	else
	{
		b->l = merge(a, b->l);
		b->upd();
		return b;
	}
}
pn split(node *a, int k)
{
	if (!a)
		return pn(0, 0);
	if (a->sz() < k)
	{
		pn nw = split(a->r, k - a->sz() - 1);
		a->r = nw.a;
		a->upd();
		nw.a = a;
		return nw;
	}
	pn nw = split(a->l, k);
	a->l = nw.b;
	a->upd();
	nw.b = a;
	return nw;
}
int getk(node *rt, int a)
{
	if (!rt)
		return 0;
	if (rt->v < a)
		return getk(rt->r, a) + rt->sz() + 1;
	else return getk(rt->l, a);
}
void ins(int a)
{
	in[a]++;
	int k = getk(root, a);
	pn sd = split(root, k);
	root = merge(merge(sd.a, new node(a)), sd.b);
}
int getx(node *rt, int a)
{
	if (!rt)
		return -1;
	if (rt->sz() >= a)
		return getx(rt->l, a);
	if (rt->sz() + 1 == a)
		return rt->v;
	return getx(rt->r, a - rt->sz() - 1);
}
void del(int a)
{
	in[a]--;
	int b = getk(root, a);
	pn t = split(root, b);
	pn u = split(t.b, 1);
	delete u.a;
	root = merge(t.a, u.b);
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int cm;
		int nm;
		scanf("%d%d", &cm, &nm);
		if (cm == 1)
			ins(nm);
		else if (cm == 4)
		{
			printf("%d\n", getx(root, getk(root, nm)));
		}
		else if (cm == 3)
		{
			printf("%d\n", getx(root, nm));
		}
		else if (cm == 2)
		{
			if (in[nm])
				del(nm);
		}
	}
}
