#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
struct node
{
	int to[36];
	int par;
	int l, fr;
	int right[11];
}ns[1010101];
int nn = 1;
int root = 1, last = 1;
void add(int s, int b)
{
	int p = last;
	int np = ++nn;
	last = np;
	ns[np].fr = ns[np].l = ns[p].l + 1;
	while (p && !ns[p].to[s])
		ns[p].to[s] = np, p = ns[p].par;
	if (!p)
		ns[np].par = root;
	else
	{
		int q = ns[p].to[s];
		if (ns[q].l == ns[p].l + 1)
			ns[np].par = q;
		else
		{
			int nq = ++nn;
			memcpy(ns[nq].to, ns[q].to, sizeof(ns[q].to));
			ns[nq].par = ns[q].par;
			ns[nq].fr = ns[q].fr;
			ns[q].par = nq;
			ns[np].par = nq;
			ns[nq].l = ns[p].l + 1;
			while (p && ns[p].to[s] == q)
				ns[p].to[s] = nq, p = ns[p].par;
		}
	}
	ns[np].right[b] = 1;
}
char s[505050];
int rd[1010101];
int l[1010101], r[1010101];
int ap[505050][26];
int bel[505050];
int sn = 1;
const int mod = 1e9 + 7;
pair<int, int> ps[27];
#define mp make_pair
int main()
{
	freopen("bainima.in", "r", stdin);
	freopen("bainima.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s + sn);
		int l = strlen(s + sn);
		for (int j = sn; j < sn + l; j++)
			bel[j] = i, add(s[j] -= 'a', i);
		s[sn + l] = i + 26;
		bel[sn + l] = i + 26;
		sn += l + 1;
		add(i + 26, 10);
	}
	for (int i = 2; i <= nn; i++)
		rd[ns[i].par]++;
	queue<int> q;
	for (int i = 2; i <= nn; i++)
		if (!rd[i])
			q.push(i);
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		int par = ns[nw].par;
		r[nw] = ns[nw].fr - ns[par].l;
		l[nw] = ns[nw].fr - ns[nw].l + 1;
		if (par == root)
			continue;
		for (int i = 0; i < n; i++)
			ns[par].right[i] += ns[nw].right[i];
		if (!--rd[par])
			q.push(par);
	}
	for (int i = 1; i < sn; i++)
		if (s[i] < 26)
			memcpy(ap[i], ap[i - 1], sizeof(ap[i - 1])), ap[i][s[i]] = i;
	long long all = 0;
	for (int i = 2; i <= nn; i++)
	{
		if (s[ns[i].fr] >= 26 || bel[l[i]] != bel[r[i]])
			continue;
		long long ans = 1;
		int fl = 0;
		for (int j = 0; j < n; j++)
			if (ns[i].right[j])
				ans = ans * ns[i].right[j] % mod, fl++;
		if (fl <= 1)
			continue;
		int mn = s[ns[i].fr], mx = s[ns[i].fr];
		int np = 0;
		for (int j = 0; j < 26; j++)
			if (ap[ns[i].fr][j] >= l[i])
				ps[np++] = mp(ap[ns[i].fr][j], j);
		sort(ps, ps + np);
		long long t = 0;
		int nps = ns[i].fr;
		for (int j = np - 1; j >= 0; j--)
		{
			t += max(0, (min(nps, r[i]) - ps[j].first)) * (mn + 1ll) * (mx + 1);
			nps = ps[j].first, mn = min(ps[j].second, mn), mx = max(ps[j].second, mx);
		}
		t += (min(nps, r[i]) - l[i] + 1ll) * (mn + 1) * (mx + 1);
		t %= mod;
		all += ans * t % mod;
	}
	all %= mod;
	printf("%lld", all);
}
