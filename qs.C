#include <cstdio>
#include <queue>
using namespace std;
unsigned long long g[55][55];
unsigned long long f[55][55];
const long long mx = 1e18;
int n, m, x1, y1, x2, y2;
int ans[110];
int na;
int os[4][2] = {{1, -2}, {1, 2}, {2, -1}, {2, 1}};
int dfs(int x, int y)
{
	if (x == n && y == m)
		return 1;
	if (x > n || y > m || x <= 0 || y <= 0)
		return 0;
	for (int i = 0; i < 4; i++)
	{
		if (dfs(x + os[i][0], y + os[i][1]))
		{
			ans[na++] = x + os[i][0];
			ans[na++] = y + os[i][1];
			return 1;
		}
	}
}
bool vd[4096];
int main()
{
	scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2);
	if ((x1 || x2 || y1 || y2) == 0)
	{
		if (!dfs(1, 1))
		{
			printf("NO");
			return 0;
		}
		printf("(1,1)");
		for (; na; na -= 2)
			printf("-(%d,%d)", ans[na - 2], ans[na - 1]);
	}
	else
	{
		f[x1][y1] = 1;
		for (int i = x1 + 1; i <= x2; i++)
			for (int j = 1; j <= m; j++, f[i][j] %= (long long)1e18)
				f[i][j] = f[i - 2][j - 1] + f[i - 2][j + 1] + f[i - 1][j - 2] + f[i - 1][j + 2];
		printf("%I64d", f[x2][y2]);
	}
}
