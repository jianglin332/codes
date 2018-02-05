#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;
struct ed
{
	int to, c, nx;
}es[2020];
int hd[55], ne;
int d[55], d2[55], head[55];
bool bfs(int s)
{
	memset(d, -1, sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 0;
	bool ret = 0;
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		ret |= nw == 0;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (d[es[i].to] == -1 && es[i].c)
			{
				q.push(es[i].to);
				d[es[i].to] = d[nw] + 1;
			}
	}
	return ret;
}
int dfs(int nw, int c)
{
	if (!nw)
		return c;
	int fl = c;
	for (int &i = head[nw]; i != -1; i = es[i].nx)
		if (es[i].c && d[es[i].to] > d[nw])
		{
			int t = dfs(es[i].to, min(es[i].c, fl));
			fl -= t;
			es[i].c -= t;
			es[i ^ 1].c += t;
			if (!fl)
				return c;
		}
	return c - fl;
}
void ae(int a, int b)
{
	es[ne].to = b;
	es[ne].nx = hd[a];
	es[ne].c = 1;
	hd[a] = ne++;
}
int f[55];
int vl[55];
int main()
{
	while (1)
	{
		static int nb = 1;
		int r, t;
		scanf("%d%d", &r, &t);
		if (!r && !t)
			break;
		memset(hd, -1, sizeof(hd));
		memset(es, 0, sizeof(es));
		memset(f, 0x23, sizeof(f));
		for (int i = 0; i <= r; i++)
			vl[i] = 1;
		ne = 0;
		for (int i = 0; i < t; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			ae(a, b);
			ae(b, a);
		}
		int rm = r, mn = 0;
		while (rm)
		{
			for (int i = 1; i <= r; i++)
			{
				int mc = 0;
				for (int j = 0; j < ne; j++)
					es[j].c = vl[es[j].to];
				while (bfs(i))
				{
					memcpy(head, hd, sizeof(hd));
					mc += dfs(i, 10101010);
				}
				f[i] = min(f[i], mc + mn);
			}
			mn = 0x23333333;
			for (int i = 1; i <= r; i++)
				if (vl[i])
					mn = min(mn, f[i]);
			for (int i = 1; i <= r; i++)
				if (vl[i] && f[i] == mn)
					vl[i] = 0, rm--;
		}
		printf("Case %d: %d\n\n", nb, f[1]);
		nb++;
	}
}
