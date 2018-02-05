#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct ed
{
	int to;
	ed *nx;
	ed(int t, ed *n):to(t), nx(n){};
} *hd[200];
int f[2][200][200];
int b[200];
int v[200];
int t[200][200];
int be[200];
int ans[200];
int n, k;
const int oo = 0x33333333;
void init()
{
	memset(f, 0x33, sizeof(f));
	memset(b, 0x33, sizeof(b));
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++)
		scanf("%d", v + i);
	int s, g;
	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d%d", &s, &g);
		hd[s] = new ed(g, hd[s]);
		hd[g] = new ed(s, hd[g]);
	}
}
void work(int a, int pr)
{
	if (hd[a]->to == pr && !hd[a]->nx)
	{
		f[0][a][0] = k;
		for (int i = 1; i < n; i++)
			f[1][a][i] = min(v[i], k);
		t[a][0] = a;
		b[a] = k;
		be[a] = 0;
		return;
	}
	for (int i = 0; i < n; i++)
		f[1][a][i] = v[i];
	for (ed *i = hd[a]; i; i = i->nx)
	{
		if (i->to == pr)
			continue;
		work(i->to, a);
		for (int j = 0; j < n; j++)
		{
			f[1][a][j] += min(f[1][i->to][j + 1], b[i->to]);
			if (f[1][a][j] >= oo)
				f[1][a][j] = oo;
		}
	}
	f[0][a][0] = f[1][a][0] + k;
	f[1][a][0] = oo;
	for (int i = 0; i < n; i++)
		t[a][i] = a;
	for (ed *i = hd[a]; i; i = i->nx)
	{
		if (i->to == pr)
			continue;
		for (int j = 1; j < n; j++)
		{
			if (f[0][a][j] > f[1][a][j] - min(f[1][i->to][j + 1], b[i->to]) + f[0][i->to][j - 1])
			{
				f[0][a][j] = f[1][a][j] - min(f[1][i->to][j + 1], b[i->to]) + f[0][i->to][j - 1];
				t[a][j] = i->to;
			}
		}
	}
	be[a] = 0;
	for (int i = 0; i < n; i++)
	{
		if (f[0][a][i] < b[a])
		{
			b[a] = f[0][a][i];
			be[a] = i;
		}
	}
}
int find(int, int, int);
int find1(int nd, int dis, int par)
{
	if (dis == 0)
	{
		ans[nd] = nd;
	}
	else
		ans[nd] = find1(t[nd][dis], dis - 1, nd);
	for (ed *i = hd[nd]; i; i = i->nx)
	{
		if (i->to == par || i->to == t[nd][dis])
			continue;
		find(i->to, dis + 1, nd);
	}
	return ans[nd];
}
int find(int nd, int dis, int par)
{
	if (b[nd] <= f[1][nd][dis])
	{
		if (t[nd][be[nd]] == nd)
			ans[nd] = nd;
		else
			ans[nd] = find1(t[nd][be[nd]], be[nd] - 1, nd);
		for (ed *i = hd[nd]; i; i = i->nx)
		{
			if (i->to == par || i->to == t[nd][be[nd]])
				continue;
			find(i->to, be[nd] + 1, nd);
		}
	}
	else
	{
		ans[nd] = ans[par];
		for (ed *i = hd[nd]; i; i = i->nx)
		{
			if (i->to == par)
				continue;
			find(i->to, dis + 1, nd);
		}
	}
	return ans[nd];
}
int main()
{
	init();
	work(1, 0);
	printf("%d\n", b[1]);
	find(1, 0, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	return 0;
}
