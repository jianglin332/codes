#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
struct ed
{
	int to, nx, c, cost;
}es[50505];
int hd[555], head[555], ne;
int S = 553, T = 554;
void ae(int f, int t, int c, int cost)
{
	es[ne].to = t;
	es[ne].c = c;
	es[ne].cost = cost;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
int d[555], in[555], cv[555], tm;
int n, m;
bool spfa()
{
	queue<int> q;
	q.push(S);
	memset(d, 0x33, sizeof(d));
	d[S] = 0;
	bool ret = 0;
	tm++;
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		cv[nw] = tm;
		ret |= (nw == T);
		in[nw] = 0;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (es[i].c && es[i].cost + d[nw] < d[es[i].to])
			{
				d[es[i].to] = es[i].cost + d[nw];
				if (!in[es[i].to])
				{
					q.push(es[i].to);
					in[es[i].to] = 1;
				}
			}
	}
	return ret;
}
int np;
int dinic(int x, int c)
{
	if (x == T)
		return c;
	int cc = c;
	cv[x] = 0;
	for (int &i = head[x]; i != -1; i = es[i].nx)
		if (es[i].c && es[i].cost + d[x] == d[es[i].to] && cv[es[i].to] == tm)
		{
			int t = dinic(es[i].to, min(es[i].c, c));
			es[i].c -= t;
			es[i ^ 1].c += t;
			c -= t;
			np += es[i].cost * t;
			if (!c)
				return cc;
		}
	return cc - c;
}
int space[15];
int s[55][15], t[55][15], k[55], tim[55][15];
struct e
{
	int n, num, ord, t, t2;
	bool operator<(const e &a) const
	{
		if (num == a.num)
			return ord > a.ord;
		return num < a.num;
	}
}ees[55];
bool cmp(const e &a, const e &b)
{
	return a.n < b.n;
}
int main()
{
	scanf("%d%d", &m, &n);
	memset(hd, -1, sizeof(hd));
	for (int i = 1; i <= m; i++)
		scanf("%d", space + i);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", k + i);
		for (int j = 0; j < k[i]; j++)
			scanf("%d%d", &s[i][j], &t[i][j]);
	}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			int ns = space[i];
			if (ns < s[j][0])
				continue;
			int st = 0, ed = k[j];
			while (st + 1 < ed)
			{
				int mid = (st + ed) / 2;
				if (s[j][mid] <= ns)
					st = mid;
				else
					ed = mid;
			}
			int tm = tim[j][i] = t[j][st];
			for (int l = 1; l <= n; l++)
			{
				ae(j, i * 50 + l, 1, tm * l);
				ae(i * 50 + l, j, 0, -tm * l);
			}
		}
	for (int i = 1; i <= n; i++)
		ae(S, i, 1, 0), ae(i, S, 0, 0);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			ae(i * 50 + j, T, 1, 0), ae(T, i * 50 + j, 0, 0);
	while (spfa())
	{
		memcpy(head, hd, sizeof(head));
		dinic(S, 111);
	}
	printf("%.2lf\n", np / (n * 1.));
	for (int i = 1; i <= n; i++)
		for (int j = hd[i]; j != -1; j = es[j].nx)
			if (!es[j].c)
			{
				ees[i].n = i, ees[i].num = (es[j].to - 1) / 50, ees[i].ord = (es[j].to - 1) % 50 + 1;
				break;
			}
	sort(ees + 1, ees + 1 + n);
	int pr = -1, pt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (ees[i].num != pr)
		{
			pr = ees[i].num;
			pt = 0;
		}
		ees[i].t = pt;
		pt = ees[i].t2 = pt + tim[ees[i].n][ees[i].num];
	}
	sort(ees + 1, ees + 1 + n, cmp);
	for (int i = 1; i <= n; i++)
		printf("%d %d %d\n", ees[i].num, ees[i].t, ees[i].t2);
}
