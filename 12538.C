#include <cstdio>
#include <cstdlib>
#include <cstring>
struct node
{
	char *a;
	int len;
	int fix;
	int siz;
	node *l, *r;
	node(int ln, char *s)
	{
		len = ln;
		a = new char[ln];
		strncpy(a, s, ln);
		fix = rand();
		siz = len;
		l = r = 0;
	}
	node(node *s)
	{
		len = s->len;
		a = s->a;
		fix = s->fix;
		siz = s->fix;
		l = s->l;
		r = s->r;
	}
	int sz()
	{
		return l ? l->siz : 0;
	}
	void upd()
	{
		siz = (r ? r->siz : 0) + (l ? l->siz : 0) + len;
	}
};
node * merge(node * a, node * b)
{
	if (!a)
		return b;
	if (!b)
		return a;
	node *nw;
	if (a->fix < b->fix)
	{
		nw = new node(a);
		nw->r = merge(a->r, b);
		nw->upd();
	}
	else
	{
		nw = new node(b);
		nw->l = merge(a, b->l);
		nw->upd();
	}
	return nw;
}
struct pn
{
	node *a, *b;
	pn(node *c, node *d):a(c), b(d){}
}
pn split(node *a, int l)
{
	if (!a)
		return pn(0, 0);
	if (a->sz() > l)
	{
		pn t = split(a->l, l);
		node *n = new node(a);
		n->l = t.b;
		n->upd();
		t.b = n;
		return t;
	}
	if (a->sz() + a->len < l)
	{
		pn t = split(a->r, l - a->sz() - a->len);
		node *n = new node(a);
		n->r = t.a;
		n->upd();
		t.a = n;
		return t;
	}
	else
	{
		pn t(new node(a), new node(a));
		t.a->r = t.b->l = 0;
		t.a->len = l - a->sz();
		t.b->len = a.len - t.a->len;
		t.a->upd();
		t.b->upd();
		t.a->a = new char[t.a->len];
		t.b->a = new char[t.b->len];
		strncpy(t.a->a, a->a, t.a->len);
		strncpy(t.b->a, a->a + t.a->len, t.b->len);
		return t;
	}
}
void insert(int p, char * s, int l)
{
	pn t = split(root[nr], p);
	root[nr++] = merge(merge(t.a, new node(l, s)), t.b);
}
void del(int p, int s)
{
	pn t = split(root[nr], p - 1);
	root[nr++] = merge(t.a, split(t.b, s).b);
}
void disp(int p, int s)
{
	d
}
int main()
{
}4
