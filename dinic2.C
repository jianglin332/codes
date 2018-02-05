#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct edge
{
	int s, t, c, n;
}es[20101];
int cw[1010], h[1010], head[1010], s = 1, t, n;
bool bfs()
{
	memset(cw, 0, sizeof(cw));
	queue<int> q;
	q.push(s);
	cw[s] = 1;
	bool ret = 0;
	while (!q.empty())
	{
		int cl = cw[q.front()] + 1;
		for (int i = h[q.front()]; i != -1; i = es[i].n)
		{
			if (es[i].c && !cw[es[i].t])
			{
				cw[es[i].t] = cl;
				q.push(es[i].t);
				if (es[i].t == n)
					ret = 1;
			}
		}
		q.pop();
	}
	return ret;
}
int dfs(int st, int _fl)
{
	int fl = _fl;
	if (st == n)
	{
		return fl;
	}
	int cl = cw[st] + 1;
	for (int &i = head[st]; i != -1; i = es[i].n)
	{
		if (cw[es[i].t] != cl || es[i].c == 0)
			continue;
		int p = dfs(es[i].t, min(fl, es[i].c));
		fl -= p;
		es[i].c -= p;
		es[i ^ 1].c += p;
		if (fl == 0)
			return _fl;
	}
	return _fl - fl;
}
int main()
{
	scanf("%d%d", &n, &t);
	memset(h, -1, sizeof(h));
	memset(head, -1, sizeof(h));
	for (int i = 0; i < (t << 1); i += 2)
	{
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		es[i].n = h[x];
		h[x] = i;
		es[i].s = es[i + 1].t = x;
		es[i].t = es[i + 1].s = y;
		es[i].c = c;
		es[i + 1].c = 0;
		es[i + 1].n = h[y];
		h[y] = i + 1;
	}
	int ans = 0;
	while (bfs())
	{
		for (int i = 1; i <= n; i++)
			head[i] = h[i];
		ans += dfs(s, 2e9);
	}
	printf("%d", ans);
}
