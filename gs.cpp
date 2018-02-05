#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct node
{
	int to[26];
	int par;
	int right, l, rd;
} ns[101010];
int nn = 1, last = 1;
void add(int x)
{
	int p = last;
	int np = last = ++nn;
	ns[np].right = 1;
	for (; p && !ns[p].to[x]; ns[p].to[x] = np, p = ns[p].par)
	if (!p)
		ns[np].par = 1;
	else
	{
		int q = ns[p].to[x];
		if (ns[p].l + 1 == ns[q].l)
			ns[np].par = q;
		else
		{
			int nq = ++nn;
			memcpy(&ns[nq], &ns[q], sizeof(ns[q]));
			ns[nq].right = 0;
			ns[nq].l = ns[p].l + 1;
			ns[np].par = ns[q].par = nq;
		}
	}
}
char s[50505], p[50505];
int ls;
int q[101010], st, ed;
int fr[50505], to[50505];
int l[101010], r[101010];
int e[101010];
void build(char *p)
{
	memset(ns, 0, sizeof(ns));
	nn = last = 1;
	int len = strlen(p);
	for (int i = 0; i < len; i++)
		add(p[i] - 'a');
	for (int i = 1; i <= nn; i++)
		ns[ns[i].par].rd++;
	st = ed = 0;
	for (int i = 1; i <= nn; i++)
		if (!ns[i].rd)
			q[ed++] = i;
	while (st < ed)
	{
		int nw = q[st++];
		ns[ns[nw].par].right += ns[nw].right;
		if (!--ns[ns[nw].par].rd)
			q[ed++] = ns[nw].par; 
	}
}
void work(int lim, int type)
{
	int now = 1, lp = 0;
	for (int i = 0; i < ls; i++)
	{
		if (ns[now].to[s[i] - 'a'])
			lp++, now = ns[now].to[s[i] - 'a'];
		else
		{
			for (; now && !ns[now].to[s[i] - 'a']; now = ns[now].par);
			if (!now)
				now = 1, lp = 0;
			else
				now = ns[now].to[s[i] - 'a'], lp = ns[now].l;
		}
		while (now && ns[now].right < lim)
			now = ns[now].par;
		if (type)
			fr[i] = max(fr[i], lp + 1);
		else
			to[i] = min(to[i], lp);
	}
}
int main()
{
	scanf("%s", s);
	ls = strlen(s);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int l, r;
		scanf("%s%d%d", p, &l, &r);
		build(p);
		if (l)
			work(l, 0);
		work(r + 1, 1);
	}
	build(s);
	for (int i = 1; i <= nn; i++)
		l[i] = ns[ns[i].par].l + 1, r[i] = ns[i].l;
	int now = 1, lp = 0;
	for (int i = 0; i < ls; i++)
	{
		if (ns[now].to[s[i] - 'a'])
			lp++, now = ns[now].to[s[i] - 'a'];
		else
		{
			for (; now && !ns[now].to[s[i] - 'a']; now = ns[now].par);
			if (!now)
				now = 1, lp = 0;
			else
				now = ns[now].to[s[i] - 'a'], lp = ns[now].l;
		}
		while (now && lp >= fr[i])
		{
			if (ns[ns[now].par].l >= fr[i] - 1)
				now = ns[now].par, lp = ns[now].l;
			else
				lp = fr[i] - 1;
		}
		l[i] = max(l[i], lp + 1);
		e[now] |= 1;
		if (!now)
			now = 1;
	}
	now = 1, lp = 0;
	for (int i = 0; i < ls; i++)
	{
		if (ns[now].to[s[i] - 'a'])
			lp++, now = ns[now].to[s[i] - 'a'];
		else
		{
			for (; now && !ns[now].to[s[i] - 'a']; now = ns[now].par);
			if (!now)
				now = 1, lp = 0;
			else
				now = ns[now].to[s[i] - 'a'], lp = ns[now].l;
		}
		while (now && lp > to[i])
		{
			if (ns[ns[now].par].l >= to[i])
				now = ns[now].par, lp = ns[now].l;
			else
				lp = to[i];
		}
		r[i] = min(r[i], lp);
		e[now] |= 1;
		e[ns[now].par] = -1;
		if (!now)
			now = 1;
	}
	for (int i = 1; i <= nn; i++)
		ns[ns[i].par].rd++;
	st = ed = 0;
	for (int i = 1; i <= nn; i++)
		if (!ns[i].rd)
			q[ed++] = i;
	while (st < ed)
	{
		int nw = q[st++];
		ns[ns[nw].par].right += ns[nw].right;
		e[ns[nw].par] |= e[nw];
		if (!--ns[ns[nw].par].rd)
			q[ed++] = ns[nw].par; 
	}
	long long ans = 0;
	for (int i = 2; i <= nn; i++)
		if (e[i] == 1)
			ans += r[i] - l[i] + 1;
	printf("%lld", ans);
}
