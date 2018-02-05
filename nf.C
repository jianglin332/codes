#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
inline int min(const int a, const int b)
{
	return a < b ? a : b;
}
struct edge
{
	int nx, c, a, b;
}es[20202];
int head[10101], h[10101], cw[10101];
int n, m, st = 1;
void init()
{
	memset(h, -1, sizeof(h));
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < (m << 1); i += 2)
	{
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		es[i].nx = h[x];
		es[i].a = x;
		es[i].b = y;
		es[i].c = c;
		es[i + 1].nx = h[y];
		es[i + 1].a = y;
		es[i + 1].b = x;
		es[i + 1].c = 0;
		h[x] = i;
		h[y] = i + 1;
	}
}
bool bfs()
{
	memset(cw, 0, sizeof(cw));
	queue<int> q;
	q.push(st);
	cw[1] = 1;
	bool ret = 0;
	while (!q.empty())
	{
		int cl = cw[q.front()] + 1;
		for (int i = h[q.front()]; i != -1; i = es[i].nx)
		{
			if (cw[es[i].b] != 0 || es[i].c == 0)
				continue;
			if (es[i].b == n)
				ret = 1;
			cw[es[i].b] = cl;
			q.push(es[i].b);
		}
		q.pop();
	}
	return ret;
}
int dfs(int nd, int _f)
{
	if (nd == n)
		return _f;
	int f = _f;
	int cl = cw[nd] + 1;
	for (int &i = head[nd]; i != -1; i = es[i].nx)
	{
		int b = es[i].b;
		if (cw[b] != cl || es[i].c <= 0)
			continue;
		int t = dfs(es[i].b, min(f, es[i].c));
		f -= t;
		es[i].c -= t;
		es[i ^ 1].c += t;
		if (!f)
			return _f;
	}
	return _f - f;
}
int main()
{
	init();
	int ans = 0;
	while (bfs())
	{
		for (int i = 1; i <= n; i++)
			head[i] = h[i];
		ans += dfs(1, 2147483647);
	}
	printf("%d\n", ans);
}
