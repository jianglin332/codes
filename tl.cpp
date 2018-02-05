#include <stdio.h>
#include <ctype.h>
#include <string.h>
struct nd
{
	nd *go[26], *par;
	int val;
	nd(int vl):val(vl), par(0)
	{
		memset(go, 0, sizeof(go));
	}
} *root, *last;
void ins(char t)
{
	nd *p = last;
	nd *np = new nd(p->val + 1);
	while (p && !p->go[t])
		p->go[t] = np, p = p->par;
	if (!p)
		np->par = root;
	else
	{
		nd *q = p->go[t];
		if (p->val + 1 == q->val)
			np->par = q;
		else
		{
			nd *nq = new nd(p->val + 1);
			memcpy(nq->go, q->go, sizeof(q->go));
			nq->par = q->par;
			q->par = np->par = nq;
			while (p && p->go[t] == q)
				p->go[t] = nq, p = p->par;
		}
	}
	last = np;
}
int main()
{
	last = root = new nd(0);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		char c = 0;
		while (!isalpha(c = getchar()));
		ins(c - 'A');
	}
	nd *nw = root;
	int ans = 1;
	for (int i = 0; i < m; i++)
	{
		char c = 0;
		while (!isalpha(c = getchar()));
		c -= 'A';
		if (nw->go[c])
			nw = nw->go[c];
		else
			ans++, nw = root->go[c];
	}
	printf("%d", ans);
}
