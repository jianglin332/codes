#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
struct ed
{
	int to, nx, fl;
}es[20202];
int hd[1010], ne;
int n, m;
void addEdge(int fr, int to, int fl)
{
	es[ne].to = to;
	es[ne].nx = hd[fr];
	es[ne].fl = fl;
	hd[fr] = ne++;
	es[ne].to = fr;
	es[ne].nx = hd[to];
	es[ne].fl = 0;
	hd[to] = ne++;
}
int h[1010], head[1010];
bool bfs()
{
	memset(h, -1, sizeof(h));
	queue<int> q;
	q.push(1);
	bool ret = 0;
	h[1] = 0;
	while (!q.empty())
	{
		int now = q.front();
		q.pop();
		for (int i = hd[now]; i != -1; i = es[i].nx)
			if (h[es[i].to] == -1 && es[i].fl > 0)
			{
				if (es[i].to == m)
					ret = 1;
				h[es[i].to] = h[now] + 1;
				q.push(es[i].to);
			}
	}
	return ret;
}
int dinic(int now, int mx)
{
	if (now == m)
		return mx;
	int org = mx;
	for (int &i = head[now]; i != -1; i = es[i].nx)
		if (h[es[i].to] > h[now] && es[i].fl)
		{
			int ok = dinic(es[i].to, min(mx, es[i].fl));
			es[i].fl -= ok;
			es[i ^ 1].fl += ok;
			mx -= ok;
			if (mx == 0)
				return org;
		}
	return org - mx;
}
int main()
{
	memset(hd, -1, sizeof(hd));
	memset(head, -1, sizeof(head));
	scanf("%d%d", &m, &n);
	for (int i = 0; i < n; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
	}
	long long ans = 0;
	int tmp = 0;
	while (bfs())
	{
		for (int i = 1; i <= m; i++)
			head[i] = hd[i];
		ans += dinic(1, 0x7FFFFFFF);
	}
	printf("%I64d\n", ans);
	return 0;
}
