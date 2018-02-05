#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
struct node
{
	int par, to[36];
	int l, r, right[10], fr;
}ns[1010101];
int root, last, nn;
void add(int x, int n)
{
	int p = last;
	int np = ++nn;
	ns[np].right[n] = 1;
	last = np;
	ns[np].fr = ns[np].l = ns[p].l + 1;
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
			int nq = ++nn;
			memcpy(ns[nq].to, ns[q].to, sizeof(ns[nq].to));
			ns[nq].par = ns[q].par;
			ns[nq].fr = ns[np].fr;
			ns[q].par = nq;
			ns[np].par = nq;
			ns[nq].l = ns[p].l + 1;
			while (p && ns[p].to[x] == q)
				ns[p].to[x] = nq, p = ns[p].par;
		}
	}
}
char s[505050];
int bel[505050];
int in[1010101];
int q[1010101];
int pos[26];
int ap[505050][26];
struct e
{
	int pos, val;
	e(){}
	e(int p, int v)
	{
		pos = p, val = v;
	}
	bool operator<(const e &a) const
	{
		return pos > a.pos;
	}
};
const long long mod = 1000000007;
int main()
{
	freopen("bainima.in", "r", stdin);
	freopen("bainima.out", "w", stdout);
	int n;
	scanf("%d", &n);
	root = last = nn = 1;
	memset(ap, -1, sizeof(ap));
	memset(pos, -1, sizeof(pos));
	int sl = 1;
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s + sl);
		int ls = strlen(s + sl);
		for (int j = 0; j < ls; j++)
			bel[sl + j] = i, add(s[sl + j] -= 'a', i);
		s[sl + ls] = 26 + i;
		bel[sl + ls] = 26 + i;
		add(26 + i, i);
		sl += ls + 1;
	}
	for (int i = 1; i <= nn; i++)
	{
		in[ns[i].par]++;
		ns[i].r = ns[ns[i].par].l + 1;
	}
	int st = 0, ed = 0;
	for (int i = 1; i <= nn; i++)
		if (!in[i])
			q[ed++] = i;
	while (st < ed)
	{
		int nw = q[st++];
		for (int i = 0; i < n; i++)
			ns[ns[nw].par].right[i] += ns[nw].right[i];
		if (ns[nw].par && !--in[ns[nw].par])
			q[ed++] = ns[nw].par;
	}
	for (int i = 1; i < sl; i++)
		if (s[i] < 26)
		{
			pos[s[i]] = i;
			for (int j = 0; j < 26; j++)
				ap[i][j] = pos[j];
		}
	long long tot = 0;
	for (int i = 2; i <= nn; i++)
	{
		int l = ns[i].fr - ns[i].l + 1;
		int r = ns[i].fr - ns[i].r + 1;
		if (s[ns[i].fr] >= 26 || bel[l] != bel[r])
			continue;
		e q[26];
		int ne = 0;
		for (int j = 0; j < 26; j++)
			if (ap[ns[i].fr][j] != -1)
				q[ne++] = e(ap[ns[i].fr][j], j);
		sort(q, q + ne);
		int nw = ns[i].fr, mn = s[nw], mx = s[nw];
		long long ans = 0;
		for (int j = 0; j < ne && q[j].pos >= l; j++)
		{
			ans += max(min(nw, r) - q[j].pos, 0) * (mn + 1) * (mx + 1);
			nw = q[j].pos;
			mn = min(mn, q[j].val);
			mx = max(mx, q[j].val);
		}
		ans += (min(nw, r) - l + 1) * (mn + 1) * (mx + 1);
		int cnt = 0;
		for (int j = 0; j < n; j++)
			if (ns[i].right[j])
			{
				cnt++;
				ans = ans * ns[i].right[j] % mod;
			}
		if (cnt >= 2)
			tot = (tot + ans) % mod;
	}
	printf("%lld", tot);
}
