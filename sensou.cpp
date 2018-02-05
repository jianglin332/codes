#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
struct ed
{
	int to, nx, c, cost;
}es[101010];
int hd[5050], head[5050], d[5050], ne, S = 5049, T = 5048, vd[5050], nv;
int n, m, r, c;
void ae(int f, int t, int c, int cost)
{
	es[ne].to = t;
	es[ne].nx = hd[f];
	es[ne].c = c;
	es[ne].cost = cost;
	hd[f] = ne++;
	es[ne].to = f;
	es[ne].nx = hd[t];
	es[ne].c = 0;
	es[ne].cost = -cost;
	hd[t] = ne++;
}
bool in[5050];
bool spfa()
{
	nv++;
	queue<int> q;
	memset(d, 0xEE, sizeof(d));
	d[S] = 0;
	q.push(S);
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		in[nw] = 0;
		vd[nw] = nv;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (es[i].c && d[nw] + es[i].cost > d[es[i].to])
			{
				d[es[i].to] = d[nw] + es[i].cost;
				if (!in[es[i].to])
					in[es[i].to] = 1, q.push(es[i].to);
			}
	}
	memcpy(head, hd, sizeof(hd));
	return d[T] > 0;
}
bool dfs(int a)
{
	if (a == T)
		return 1;
	vd[a] = 0;
	for (int &i = head[a]; i != -1; i = es[i].nx)
		if (es[i].c && vd[es[i].to] == nv && d[a] + es[i].cost == d[es[i].to])
			if (dfs(es[i].to))
			{
				es[i].c = 0;
				es[i ^ 1].c = 1;
				return 1;
			}
	return 0;
}
char mp[55][55];
void add(int i, int j, int x, int y)
{
	if (x > m || y > n || x < 0 || y < 0 || mp[x][y] != '.')
		return;
	ae(i * 100 + j * 2 + 1, x * 100 + y * 2, 1, 0);
}
int main()
{
	memset(hd, -1, sizeof(hd));
	scanf("%d%d%d%d", &m, &n, &r, &c);
	for (int i = 0; i < m; i++)
		scanf("%s", mp[i]);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (mp[i][j] == '.')
			{
				ae(S, i * 100 + j * 2, 1, 0);
				ae(i * 100 + j * 2 + 1, T, 1, 0);
				ae(i * 100 + j * 2, i * 100 + j * 2 + 1, 1, 1);
				add(i, j, i + r, j + c);
				add(i, j, i + r, j - c);
				if (r != c)
				{
					add(i, j, i + c, j + r);
					add(i, j, i + c, j - r);
				}
			}
	int ans = 0;
	while (spfa())
		while (dfs(S))
			ans++;
	printf("%d", ans);
	return 0;
}
