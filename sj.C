#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
int f[505][101];
int g[101];
struct ed
{
	int to, nx, l;
	ed(){}
	ed(int t, int n, int len):to(t), nx(n), l(len){}
}es[505], fs[505];
int hd[101], sd[101], ne, nf;
int n, m;
bool nv[101];
int h[101];
void spfa(int a)
{
	queue<int> q;
	q.push(2);
	bool in[101] = {0};
	in[2] = 1;
	f[a][2] = 0; 
	while (!q.empty())
	{
		int nw = q.front();
		int v = f[a][nw];
		in[nw] = 0;
		for (int i = sd[nw]; i != -1; i = fs[i].nx)
		{
			if (nv[i])
				continue;
			if (v + fs[i].l < f[a][fs[i].to])
			{
				f[a][fs[i].to] = v + fs[i].l;
				if (!in[fs[i].to])
				{
					in[fs[i].to] = 1;
					q.push(fs[i].to);
				}
			}
		}
		q.pop();
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(hd, -1, sizeof(hd));
	memset(sd, -1, sizeof(sd));
	memset(f, 0x23, sizeof(f));
	memset(h, 0x23, sizeof(h));
	for (int i = 0; i < m; i++)
	{
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		if (a == b)
			continue;
		es[ne] = ed(b, hd[a], l);
		hd[a] = ne++;
		fs[nf] = ed(a, sd[b], l);
		sd[b] = nf++;
	}
	for (int i = 0; i < nf; i++)
	{
		nv[i] = 1;
		if (i)
			nv[i - 1] = 0;
		spfa(i);
	}
	for (int i = 1; i <= n; i++)
	{
		int mx = 0;
		bool flg = 0;
		for (int j = hd[i]; j != -1; j = es[j].nx)
		{
//			printf("%d %d\n", i, f[j][i]);
			flg = 1;
			if (mx < f[j][i])
				mx = f[j][i];
		}
		if (flg)
			h[i] = mx;
	}
//	for (int i = 1; i <= n; i++)
//		printf("%d : %d\n", i, h[i]);
	memset(g, 0x33, sizeof(g));
	queue<int> q;
	q.push(2);
	bool in[101] = {0};
	g[2] = 0;
	in[2] = 1;
	while (!q.empty())
	{
		int nw = q.front();
		int t = g[nw];
		in[nw] = 0;
		for (int i = sd[nw]; i != -1; i = fs[i].nx)
		{
			int v = max(h[fs[i].to], t + fs[i].l);
			if (g[fs[i].to] > v)
			{
				g[fs[i].to] = v;
				if (!in[fs[i].to])
				{
					in[fs[i].to] = 1;
					q.push(fs[i].to);
				}
			}
		}
		q.pop();
	}
	printf("%d", g[1]);
}

