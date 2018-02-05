#include <stdio.h>
#include <string.h>
char t[3][10101];
int f[8][10101];
const int mod = 1e9 + 7;
void dfs(int st, int l, int d, int ns, int lim = 1)
{
	if (d == 3)
	{
		f[ns][l] += f[st][l - 1];
		if (f[ns][l] >= mod)
			f[ns][l] -= mod;
		return;
	}
	if ((st >> d) & 1)
	{
		if (t[d][l] != '.')
			return;
		else if (lim || t[d][l + 1] != 'O')
			dfs(st, l, d + 1, ns, lim);
	}
	else if (t[d][l] != '.')
		dfs(st, l, d + 1, ns, lim);
	else
	{
		if (lim || t[d][l - 1] != 'O')
			dfs(st, l, d + 1, ns | (1 << d), lim);
		if (d < 2 && t[d + 1][l] == '.' && (!((st >> d + 1) & 1)) && (lim || !((d == 0 && t[2][l] == 'O') || (d == 1 && t[0][l] == 'O'))))
			dfs(st, l, d + 2, ns, lim);
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	scanf("%s%s%s", t[0] + 1, t[1] + 1, t[2] + 1);
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!f[j][i - 1])
				continue;
			dfs(j, i, 0, 0);
		}
	}
	int ans = f[0][n];
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!f[j][i - 1])
				continue;
			dfs(j, i, 0, 0, 0);
		}
	}
	ans = (ans + mod - f[0][n]) % mod;
	printf("%d", ans);
}
