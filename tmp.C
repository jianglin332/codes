#include <cstdio>
#include <algorithm>
using namespace std;
int f[101][101][21];
int r, c, m, n;
inline int g(int r, int c, int h, int l)
{
	return r * h + c * l - h * l;
}
int nr, nc;
bool ir[101], ic[101];
int x[22], y[22];
int dfs(int a)
{
	if (a == n)
	{
		int t = g(r, c, nc, nr);
		if (t >= m + n)
			return t;
		else
			return t + f[r - nr][c - nc][m + n - t];
	}
	if (ir[x[a]] || ic[y[a]])
		return dfs(a + 1);
	ir[x[a]] = 1;
	nr++;
	int mn = dfs(a + 1);
	nr--;
	ir[x[a]] = 0;
	ic[y[a]] = 1;
	nc++;
	mn = min(mn, dfs(a + 1));
	nc--;
	ic[y[a]] = 0;
	return mn;
}
int main()
{
	scanf("%d%d%d%d", &r, &c, &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d%d", x + i, y + i);
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
			for (int k = 1; k <= min(m, i * j); k++)
			{
				int mn = 99999;
				for (int l = 0; l <= k / i + (k % i != 0); l++)
					mn = min(mn, (j - l) ? ((k - i * l > 0) ? g(i, j, l, (k - i * l) / (j - l) + ((k - i * l) % (j - l) != 0)) : i * l) : i * j);
				f[i][j][k] = mn;
				printf("%d %d %d : %d\n", i, j, k, mn);
			}
	printf("%d", dfs(0));
}
