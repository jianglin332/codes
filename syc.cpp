#include <stdio.h>
#include <string.h>
#include <queue>
struct ed
{
	int to, nx, c;
}es[10101];
int hd[101], h[101], head[101];
int ne, n, m, s, t;
std::queue<int> q;
bool bfs()
{
	q.push(s);
	memset(h, -1, sizeof(h));
	h[s] = 0;
	bool ret = 0;
	while (!q.empty())
	{
		int nw = q.front();
		ret |= nw == t;
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
	if (nw == t)
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
void ae(int a, int b, int c)
{
	es[ne].to = b;
	es[ne].c = c;
	es[ne].nx = hd[a];
	hd[a] = ne++;
}
int main()
{
	scanf("%d%d%d%d", &n, &s, &t, &m);
	memset(hd, -1, sizeof(hd));
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		ae(a, b, c);
		ae(b, a, c);
	}
	int ans = 0;
	while (bfs())
	{
		memcpy(head, hd, sizeof(hd));
		ans += dfs(s, 1010101);
	}
	printf("%d", ans);
}
