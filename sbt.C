#include <cstdio>
#include <algorithm>
using namespace std;
typedef int vt;
struct node	
{
	int size;
	vt value;
	node *lch, *rch;
	node(){}
	node(vt a)
	{
		size = 1;
		lch = rch = NULL;
		value = a;
	}
	void upt()
	{
		size = (lch == NULL ? 0 : lch->size) + (rch == NULL ? 0 : rch->size) + 1;
	}
} *root = NULL;
inline int gett(node *a)
{
	return a == NULL ? 0 : a->size;
}
void rrot(node *&a)
{
	node *t = a->lch;
	a->lch = t->rch;
	t->rch = a;
	a = t;
	a->size = a->rch->size;
	a->rch->upt();
}
void lrot(node *&a)
{
	node *t = a->rch;
	a->rch = t->lch;
	t->lch = a;
	a = t;
	a->size = a->lch->size;
	a->lch->upt();
}
void mt(node *&a)
{
	if (!a)
		return;
	if (a->lch && gett(a->lch->lch) > gett(a->rch))
	{
		rrot(a);
		mt(a->rch);
		mt(a);
		return;
	}
	if (a->lch && gett(a->lch->rch) > gett(a->rch))
	{
		lrot(a->lch);
		rrot(a);
		mt(a->lch);
		mt(a->rch);
		mt(a);
		return;
	}
	if (a->rch && gett(a->rch->rch) > gett(a->lch))
	{
		lrot(a);
		mt(a->lch);
		mt(a);
		return;
	}
	if (a->rch && gett(a->rch->lch) > gett(a->lch))
	{
		rrot(a->rch);
		lrot(a);
		mt(a->lch);
		mt(a->rch);
		mt(a);
		return;
	}
}
void insert(vt b, node *&rt)
{
	if (rt == NULL)
	{
		rt = new node(b);
		return;
	}
	if (b <= rt->value)
		insert(b, rt->lch);
	else
		insert(b, rt->rch);
	rt->size++;
	mt(rt);
}
int getr(vt a)
{
	node *rt = root;
	int bs = 0, rm = 2147483647;
	bool found;
	while (rt)
	{
		if (a < rt->value)
		{
			rt = rt->lch;
			continue;
		}
		if (a == rt->value)
		{
			if (rm >  bs + gett(rt->lch))
				rm = bs + gett(rt->lch);
			rt = rt->lch;
			continue;
		}
		bs += gett(rt->lch) + 1;
		rt = rt->rch;
	}
	if (rm == 2147483647)
		return -1;
	else
		return rm + 1;
}
vt getk(int a)
{
	node *rt = root;
	int t = a;
	if ((!rt) || (rt->size < a) || a < 1)
		return -1;
	while (rt)
	{
		int d = gett(rt->lch) + 1;
		if (t < d)
		{
			rt = rt->lch;
			continue;
		}
		if (t == d)
		{
			return rt->value;
		}
		t -= d;
		rt = rt->rch;
	}
}
void disp(node *a, int d)
{
	static int md = 0;
	if (!a)
		return;
	disp(a->lch, d + 1);
	if (md < d)md = d;
	printf("%d %d\n", a->value, md);
	disp(a->rch, d + 1);
}
int mainx()
{
	int n, t;
	scanf("%d", &n);
	for (; n; n--){
		insert(n, root);
	}disp(root, 1);
}
int main()
{
	int n, a;
	char c;
	scanf("%d", &n);
	for (; n; n--)
	{
		scanf("\n%c %d", &c, &a);
		if (c == 'I')
			insert(a, root);
		else if (c == 'R')
			printf("%d\n", getr(a));
		else if (c == 'K')
			printf("%d\n", getk(a));
	}
}
