#include <stdio.h>
#include <string.h>
bool mat[777][777];
int tag[777];
int os[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
int ks[777];
char s[5];
bool vd[777];
int cd[777];
int n, m;
bool dfs(int x)
{
	for (int i = 1; i <= m; i++)
	{
		if (mat[x][i] && !vd[i])
		{
			vd[i] = 1;
			if (!cd[i] || dfs(cd[i]))
			{
				cd[i] = x;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", s);
		if (!s[2])
			ks[i] = (s[0] - 'A') * n + s[1] - '1';
		else
			ks[i] = (s[0] - 'A') * n + (s[1] - '0') * 10 + s[2] - '1';
		tag[ks[i]] = i;
	}
	for (int i = 1; i <= m; i++)
		{
			int x = ks[i] / n, y = ks[i] % n;
			for (int j = 0; j < 8; j++)
			{
				int dx = x + os[j][0], dy = y + os[j][1];
				if (dx < 0 || dy < 0 || dx >= n || dy >= n)
					continue;
				if (tag[dx * n + dy])
				{
					mat[i][tag[dx * n + dy]] = 1;
				}
			}
		}
	int ans = 0;
	for (int i = 1; i <= m; i++)
		if ((ks[i] / n + ks[i] % n) & 1)
		{
			if (dfs(i))
				ans++;
			memset(vd, 0, sizeof(vd));
		}
	printf("%d", ans);
}
