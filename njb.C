#include <cstdio>
int a[1001][1001];
int f[1001][1001], t;
inline int max(int a, int b)
{
	return a > b ? a : b;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	f[0][0] = a[0][0];
	for (int i = 1; i < n; i++)
	{
		f[0][i] = f[0][i - 1] + a[0][i];
		f[i][0] = f[i - 1][0] + a[i][0];
	}
	for (int i = 1; i < n; i++)
		for (int j = 1; j < n; j++)
			f[i][j] = max(f[i - 1][j], f[i][j - 1]) + a[i][j];
	printf("%d", f[n - 1][n - 1]);
}
