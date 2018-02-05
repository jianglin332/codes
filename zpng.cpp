#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int vl[22][22];
int lx[22], ly[22];
int inx[22], iny[22];
int cd[22], vd[22];
int x[22], y[22], n = 1, m = 1;
bool dfs(int x)
{
	inx[x] = 1;
	for (int i = 1; i < m; i++)
		if (!iny[i] && lx[x] + ly[i] == vl[x][i])
		{
			iny[i] = 1;
			if (!cd[i] || dfs(cd[i]))
			{
				cd[i] = x;
				return 1;
			}
		}
	return 0;
}
char t[11];
int main()
{
	for (int i = 1; i <= 4; i++)
	{
		scanf("%s", t + 1);
		for (int j = 1; j <= 4; j++)
			if (t[j] == '1')
				x[n] = i, y[n++] = j;
	}
	for (int i = 1; i <= 4; i++)
	{
		scanf("%s", t + 1);
		for (int j = 1; j <= 4; j++)
			if (t[j] == '1')
			{
				for (int k = 1; k < n; k++)
					vl[k][m] = abs(x[k] - i) + abs(y[k] - j);
				m++;
			}
	}
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++)
		{
			lx[i] = max(lx[i], (vl[i][j] = 10 - vl[i][j]));
		}
	for (int i = 1; i < n; i++)
	{
		while (1)
		{
			memset(inx, 0, sizeof(inx));
			memset(iny, 0, sizeof(iny));
			if (dfs(i))
				break;
			int a = 111;
			for (int j = 1; j < n; j++)
				if (inx[j])
					for (int k = 1; k < m; k++)
						if (!iny[k])
							a = min(a, lx[j] + ly[k] - vl[j][k]);
			for (int j = 1; j < n; j++)
				if (inx[j])
					lx[j] -= a;
			for (int j = 1; j < m; j++)
				if (iny[j])
					ly[j] += a;
		}
	}
	int ans = 0;
	for (int i = 1; i < m; i++)
		ans += 10 - vl[cd[i]][i];
	printf("%d", ans);
}
