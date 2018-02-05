#include <stdio.h>
#include <string.h>
struct ed
{
	int to, nx;
}es[40404];
int hd[222], ne;
int cd[222];
int vd[222];
bool dfs(int x)
{
	for (int i = hd[x]; i != -1; i = es[i].nx)
		if (!vd[es[i].to])
		{
			int to = es[i].to;
			vd[to] = 1;
			if (!cd[to] || dfs(cd[to]))
			{
				cd[to] = x;
				return 1;
			}
		}
	return 0;
}
#define lb(x) ((x) & (-(x)))
int a[222], b[222];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	memset(hd, -1, sizeof(hd));
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	for (int i = 1; i <= m; i++)
		scanf("%d", b + i);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (((a[i] ^ b[j]) + 1) - lb((a[i] ^ b[j]) + 1) == 0)
				es[ne].to = j, es[ne].nx = hd[i], hd[i] = ne++;
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans += dfs(i);
		memset(vd, 0, sizeof(vd));
	}
	printf("%d", ans);
}
