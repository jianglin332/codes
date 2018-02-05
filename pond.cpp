#include <cstdio>
int f[55][3][55][55];
int os[6][2] = {{0, 0}, {1, -2}, {2, -1}, {3, 0}, {2, 1}, {1, 2}};
int can[55][55];
int main()
{
	freopen("pond.in", "r", stdin);
	freopen("pond.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &can[i][j]);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			if (i == j && can[0][i] < 2)
				continue;
			else if (can[0][i] && can[0][j])
			{
//				printf("CAN%d %d\n", i, j);
				f[0][0][i][j] = 1;
			}
	for (int i = 0; i < n; i++)
		for (int j = 2; j >= 0; j--)
		{
			int x = i - j;
			if (x < 0)
				continue;
			for (int k = 0; k < m; k++)
				for (int l = 0; l < m; l++)
					if (f[i][j][k][l])
					{
//						printf("BEGIN: (%d, %d), (%d, %d)\n", i, k, x, l);
						for (int p = 0; p < 6; p++)
							for (int q = 0; q < 6; q++)
							{
								if (!(p || q))
									continue;
								int x1 = i + os[p][0];
								int x2 = x + os[q][0];
								int y1 = k + os[p][1];
								int y2 = l + os[q][1];
								if (y1 < 0 || y2 < 0 || y1 >= m || y2 >= m)
									continue;
								if (x1 < x2 || x1 > x2 + 2)
									continue;
								if (x1 != i && x2 <= i)
									continue;
								if (!(can[x1][y1] && can[x2][y2]))
									continue;
								if (x1 == x2 && y1 == y2 && can[x1][y1] < 2)
									continue;
								if (x2 == i && y2 == k && can[i][k] < 2)
									continue;
//								printf("%d %d %d %d ORIG (%d, %d), (%d, %d)\n", x1, x1 - x2, y1, y2, i, k, x, l);
								f[x1][x1 - x2][y1][y2] = (f[x1][x1 - x2][y1][y2] + f[i][j][k][l]) % 1000000007;
							}
					}
		}
	int ans = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			ans = (ans + f[n - 1][0][i][j]) % 1000000007;
	printf("%d", ans);
	return 0;
}

