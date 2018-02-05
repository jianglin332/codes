#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
struct ed
{
	int to, nx, c;
}es[20202];
int hd[1010], h[1010], head[1010], ne;
int n, m;
void ae(int f, int t, int c)
{
	es[ne].to = t;
	es[ne].c = c;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
queue<int> q;
int bfs()
{
	memset(h, -1, sizeof(h));
	h[1] = 0;
	int r = 0;
	q.push(1);
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		int nh = h[nw] + 1;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (h[es[i].to] == -1 && es[i].c)
			{
				h[es[i].to] = nh;
				if (es[i].to == n)
					r = 1;
				q.push(es[i].to);
			}
	}
	return r;
}
int dinic(int nw, int flow)
{
	int fl = flow;
	if (nw == n)
		return fl;
	for (int &i = head[nw]; i != -1; i = es[i].nx)
		if (es[i].c && h[es[i].to] > h[nw])
		{
			int t = dinic(es[i].to, min(es[i].c, fl));
			es[i].c -= t;
			es[i ^ 1].c += t;
			fl -= t;
			if (!fl)
				return flow;
		}
	return flow - fl;
}
int main()
{
	memset(hd, -1, sizeof(hd));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		ae(a, b, c);
		ae(b, a, 0);
	}
	long long ans = 0;
	while (bfs())
	{
		for (int i = 1; i <= n; i++)
			head[i] = hd[i];
		ans += dinic(1, 0x7fffffff);
	}
	printf("%lld", ans);
}
