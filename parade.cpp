#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct ed
{
	int to, nx, c, cost;
}es[225000];
int hd[555], head[555], dis[255][255], dist[555], ne;
int cv[555], nc;
int cost[555], ac;
int S = 511, T = 512;
int dinic(int nw)
{
	if (nw == T)
	{
		ac++;
		cost[ac] = 0;
		return 1;
	}
	cv[nw] = 0;
	for (int &i = head[nw]; i != -1; i = es[i].nx)
		if (cv[es[i].to] == nc && es[i].c && dist[es[i].to] + es[i].cost == dist[nw])
		{
			int tm = dinic(es[i].to);
			if (!tm)
				continue;
			cost[ac] += es[i].cost;
			es[i].c -= tm;
			es[i ^ 1].c += tm;
			return 1;
		}
	return 0;
}
queue<int> q;
bool inq[555];
bool spfa()
{
	memset(dist, 9, sizeof(dist));
	q.push(T);
	dist[T] = 0;
	nc++;
	bool ret = 0;
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		ret |= nw == S;
		inq[nw] = 0;
		cv[nw] = nc;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (!es[i].c && dist[nw] - es[i].cost < dist[es[i].to])
			{
				dist[es[i].to] = dist[nw] - es[i].cost;
				if (!inq[es[i].to])
				{
					q.push(es[i].to);
					inq[es[i].to] = 1;
				}
			}
	}
	return ret;
}
void ae(int fr, int to, int cost)
{
	es[ne].to = to;
	es[ne].c = 1;
	es[ne].cost = cost;
	es[ne].nx = hd[fr];
	hd[fr] = ne++;
	es[ne].to = fr;
	es[ne].c = 0;
	es[ne].cost = -cost;
	es[ne].nx = hd[to];
	hd[to] = ne++;
}
int all[255];
int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	memset(hd, -1, sizeof(hd));
	memset(dis, 9, sizeof(dis));
	memset(cost, 9, sizeof(cost));
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		dis[a][b] = min(dis[a][b], c);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (dis[i][j] < 0x09090909)
				ae(i, j + n, dis[i][j]);
	for (int i = 1; i <= n; i++)
		ae(S, i, 0), ae(i + n, T, 0);
	while (spfa())
	{
		memcpy(head, hd, sizeof(hd));
		while(dinic(S));
	}
	for (int i = 1; i <= n; i++)
		all[i] = all[i - 1] + cost[i];
	for (int i = 0; i < k; i++)
	{
		int c;
		scanf("%d", &c);
		int st = 0, ed = n + 1;
		while (st + 1 < ed)
		{
			int mid = (st + ed) / 2;
			if (cost[mid] < c)
				st = mid;
			else
				ed = mid;
		}
		printf("%d\n", all[st] + (n - st) * c);
	}
	return 0;
}
