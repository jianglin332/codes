#include <cstdio>
bool vd[65][65];
bool vn[65];
int ans[65];
int n, nn;
int dfs(int dep)
{
	if (dep == nn)
		return 1;
	for (int i = 1; i <= nn; i++)
	{
		if (!vn[i])
		{
			vn[i] = 1;
			for (int j = i + 1; j <= nn; j++)
			{
				if (!vn[j] && !vd[i][j])
				{
					vn[j] = 1;
					if (dfs(dep + 2))
					{
						vd[i][j] = 1;
						ans[dep] = i;
						ans[dep + 1] = j;
						vn[i] = 0;
						vn[j] = 0;
						return 1;
					}
					vn[j] = 0;
				}
			}
			vn[i] = 0;
		}
	}
	return 0;
}
int main()
{
	scanf("%d", &n);
	nn = 1 << n;
	for (int i = 1; i < nn; i++)
	{
		dfs(0);
		printf("<%d>%d-%d", i, ans[0], ans[1]);
		for (int i = 2; i < nn; i += 2)
			printf(",%d-%d", ans[i], ans[i + 1]);
		printf("\n");
	}
	return 0;
}
