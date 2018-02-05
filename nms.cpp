#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
int mat[10][10];
struct ed
{
	int to, nx, c;
}es[64 * 64 * 3];
int hd[133], head[133], d[133], ne;
int S = 129, T = 130;
int n;
void ae(int f, int t, int c)
{
	es[ne].to = t;
	es[ne].c = c;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
bool bfs()
{
	queue<int> q;
	q.push(S);
	memset(d, -1, sizeof(d));
	d[S] = 0;
	bool ret = 0;
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		ret |= nw == T;
		for (int i = hd[nw]; i != -1; i = es[i].nx)
			if (es[i].c && d[es[i].to] == -1)
				d[es[i].to] = d[nw] + 1, q.push(es[i].to);
	}
	memcpy(head, hd, sizeof(hd));
	return ret;
}
int dfs(int nw, int c)
{
	if (nw == T)
		return c;
	int cc = c;
	for (int &i = head[nw]; i != -1; i = es[i].nx)
		if (es[i].c && d[es[i].to] > d[nw])
		{
			int t = dfs(es[i].to, min(c, es[i].c));
			if (t)
				es[i].c -= t, es[i ^ 1].c += t, c -= t;
			if (!c)
				return cc;
		}
	return cc - c;
}
int ud[66];
bool valid()
{
	memset(hd, -1, sizeof(hd));
	ne = 0;
	for (int i = 0;  i < n * n; i++)
		ae(S, i, 1), ae(i, S, 0), ae(i + n * n, T, 1), ae(T, i + n * n, 0);
	int ans = n * n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n + 1; j++)
			if (mat[i][j])
			{
				if (j > 0 && j <= n)
					ans--;
				int t = j - 1;
				while (t && !mat[i][t])
					t--;
				for (int k = t + 1; k < j; k++)
					for (int l = mat[i][t] + 1; l < mat[i][j]; l++)
						if (!ud[l])
							ae(i * n - n + k - 1, l - 1 + n * n, 1), ae(l - 1 + n * n, i * n - n + k - 1, 0);
			}
	}
	while (bfs())
		ans -= dfs(S, 11111);
	return !ans;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &mat[i][j]), ud[mat[i][j]]++;
	for (int i = 1; i <= n * n; i++)
		if (ud[i] > 1)
		{
			printf("-1");
			return 0;
		}
	for (int i = 1; i <= n; i++)
		mat[i][0] = 0, mat[i][n + 1] = n * n + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (mat[i][j])
			{
				int t = j + 1;
				while (!mat[i][t])
					t++;
				if (mat[i][j] >= mat[i][t])
				{
					printf("-1");
					return 0;
				}
			}
	if (!valid())
	{
		printf("-1");
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			if (!mat[i][j])
			{
				int t = j + 1;
				while (!mat[i][t])
					t++;
				t = mat[i][t];
				for (int k = mat[i][j - 1] + 1; k < t; k++)
					if (!ud[k])
					{
						mat[i][j] = k;
						ud[k] = 1;
						if (valid())
						{
							break;
						}
						ud[k] = 0;
						mat[i][j] = 0;
					}
			}
	}
	for (int i = 1; i <= n; i++, printf("\n"))
		for (int j = 1; j <= n; j++)
			printf("%d ", mat[i][j]);
}

