#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
struct ed
{
	int to, nx, l, c;
	bool vld;
}es[201010];
int hd[25252], h[25252], head[25252], ohd[25252];
int dis[25252];
int ne, n, m, c, s;
std::queue<int> q;
int pas[1010], np;
int inq[25252];
bool cmp(const int a, const int b)
{
	return dis[a] < dis[b];
}
void spfa()
{
	std::queue<int> qu;
	memset(dis, 0x33, sizeof(dis));
	qu.push(1);
	dis[1] = 0;
	while (!qu.empty())
	{
		int nw = qu.front();
		qu.pop();
		inq[nw] = 0;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (dis[nw] + es[i].l < dis[es[i].to])
			{
				dis[es[i].to] = dis[nw] + es[i].l;
				if (!inq[es[i].to])
				{
					qu.push(es[i].to);
					inq[es[i].to] = 1;
				}
			}
	}
	for (int i = 1; i <= n; i++)
		for (int j = hd[i]; j != -1; j = es[j].nx)
			if (dis[i] - es[j].l == dis[es[j].to])
				es[j].vld = 1;
}
bool bfs()
{
	q.push(s);
	memset(h, -1, sizeof(h));
	h[s] = 0;
	bool ret = 0;
	while (!q.empty())
	{
		int nw = q.front();
		ret |= nw == 1;
		q.pop();
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (es[i].c && h[es[i].to] == -1)
			{
				h[es[i].to] = h[nw] + 1;
				q.push(es[i].to);
			}
	}
	return ret;
}
int dfs(int nw, int c)
{
	if (nw == 1)
		return c;
	int fl = c;
	for (int &i = head[nw]; i != -1; i = es[i].nx)
		if (es[i].c && h[es[i].to] == h[nw] + 1)
		{
			int t = dfs(es[i].to, std::min(c, es[i].c));
			es[i].c -= t;
			es[i ^ 1].c += t;
			c -= t;
			if (!c)
				return fl;
		}
	return fl - c;
}
void ae(int a, int b, int l, int vld = 0)
{
	es[ne].to = b;
	es[ne].l = l;
	es[ne].vld = vld;
	es[ne].nx = hd[a];
	hd[a] = ne++;
}
int main()
{
	scanf("%d%d%d", &n, &m, &c);
	memset(hd, -1, sizeof(hd));
	for (int i = 0; i < m; i++)
	{
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		ae(a, b, l);
		ae(b, a, l);
	}
	for (int i = 0; i < c; i++)
		scanf("%d", pas + i);
	spfa();
	std::sort(pas, pas + c, cmp);
	memcpy(ohd, hd, sizeof(hd));
	s = 25200;
	int pne = ne;
	int nw = 0;
	int ans = 0;
	while (nw < c)
	{
		memcpy(hd, ohd, sizeof(hd));
		ne = pne;
		int nd = dis[pas[nw]];
		while (nw < c && dis[pas[nw]] == nd)
		{
			ae(s, pas[nw], 0, 1);
			ae(pas[nw], s, 0);
			nw++;
		}
		for (int i = 0; i < ne; i++)
			if (es[i].vld)
				es[i].c = 1;
			else
				es[i].c = 0;
		while (bfs())
		{
			memcpy(head, hd, sizeof(hd));
			ans += dfs(s, 10101010);
		}
	}
	printf("%d", ans);
}
