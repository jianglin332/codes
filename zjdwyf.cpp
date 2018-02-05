#include <stdio.h>
#include <ctype.h>
#include <string.h>
struct node
{
	node *tr[128];
	node *par;
	int l, rd, vd, ans;
	node()
	{
		memset(tr, 0, sizeof(tr));
		par = 0;
		ans = l = rd = vd = 0;
	}
} *root, *last;
void add(int x)
{
	node *p = last;
	node *np = new node;
	np->l = p->l + 1;
	while (p && !p->tr[x])
		p->tr[x] = np, p = p->par;
	if (!p)
		np->par = root;
	else
	{
		node *q = p->tr[x];
		if (q->l == p->l + 1)
			np->par = q;
		else
		{
			node *nq = new node;
			nq->l = p->l + 1;
			memcpy(nq->tr, q->tr, sizeof(q->tr));
			nq->par = q->par;
			q->par = nq;
			np->par = nq;
			while (p && p->tr[x] == q)
				p->tr[x] = nq, p = p->par;
		}
	}
	last = np;
}
struct queue
{
	node *q[30303];
	int st, ed;
	queue()
	{
		st = ed = 0;
	}
	void push(node *n)
	{
		q[ed++] = n;
		if (ed > 30300)
			ed = 0;
	}
	bool empty()
	{
		return st == ed;
	}
	node *front()
	{
		return q[st];
	}
	void pop()
	{
		st++;
		if (st > 30300)
			st = 0;
	}
}q;
void work()
{
	q.push(root);
	while (!q.empty())
	{
		node *t = q.front();
		q.pop();
		for (int i = 0; i < 128; i++)
			if (t->tr[i])
			{
				t->tr[i]->rd++;
				if (!t->tr[i]->vd)
				{
					t->tr[i]->vd = 1;
					q.push(t->tr[i]);
				}
			}
	}
	root->ans = 1;
	q.push(root);
	int ans = -1;
	while (!q.empty())
	{
		node *t = q.front();
		q.pop();
		ans += t->ans;
		for (int i = 0; i < 128; i++)
			if (t->tr[i])
			{
				t->tr[i]->ans += t->ans;
				t->tr[i]->rd--;
				if (!t->tr[i]->rd)
					q.push(t->tr[i]);
			}
	}
	printf("%d", ans);
}
char s[15151];
void init()
{
	root = last = new node;
	scanf("%s", s);
	for (int i = 0; s[i]; i++)
		add(s[i]);
}
int main()
{
	init();
	work();
}
