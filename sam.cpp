#include <stdio.h>
#include <string.h>
struct node
{
	int par, to[26];
	int l, v, rd;
	node()
	{
		par = 0;
		v = l = 0;
		memset(to, 0, sizeof(to));
	}
}ns[2020202];
int root, last, nn;
void add(int x)
{
	int p = last;
	int np = nn++;
	last = np;
	ns[np].l = ns[p].l + 1;
	while (p && !ns[p].to[x])
		ns[p].to[x] = np, p = ns[p].par;
	if (!p)
		ns[np].par = root;
	else
	{
		int q = ns[p].to[x];
		if (ns[q].l == ns[p].l + 1)
			ns[np].par = q;
		else
		{
			int nq = nn++;
			memcpy(ns[nq].to, ns[q].to, sizeof(ns[nq].to));
			ns[nq].par = ns[q].par;
			ns[q].par = nq;
			ns[np].par = nq;
			ns[nq].l = ns[p].l + 1;
			while (ns[p].to[x] == q)
				ns[p].to[x] = nq, p = ns[p].par;
		}
	}
}
char s[1010101], t[1010101];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", s, t);
		root = last = nn = 1;
		memset(ns, 0, sizeof(ns));
		int ls = strlen(s), lt = strlen(t);
		for (int i = 0; i < ls; i++)
			add(s[i] - 'a');
		while (ns[last].l)
			ns[last].v = 1, last = ns[last].par;
		for (int i = nn - 1; i; i--)
			for (int j = 0; j < 26; j++)
				if (ns[i].to[j])
					ns[i].v += ns[ns[i].to[j]].v;
	}
}
