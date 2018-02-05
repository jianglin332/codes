#include <stdio.h>
double f[1010][1010];
int p[1010];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", p + i);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (p[i] > p[j])
				f[i][j] = 1;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;
		f[a][b] = f[b][a] = 0.5;
		for (int j = 0; j < n; j++)
			if (j != a && j != b)
			{
				f[j][a] = f[j][b] = (f[j][a] + f[j][b]) / 2;
				f[a][j] = f[b][j] = (f[a][j] + f[b][j]) / 2;
			}
	}
	double ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			ans += f[i][j];
	printf("%.7lf", ans);
}
