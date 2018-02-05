#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
bool canbeat[101][101];
char s[111];
bool vd[111];
bool exist[111];
int n, a;
int chk()
{
	queue<int> q;
	q.push(a);
	int nc = 1;
	vd[a] = 1;
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		bool *cb = canbeat[nw];
		for (int i = 0; i < n; i++)
			if (exist[i] && cb[i] && !vd[i])
				vd[i] = 1, nc++, q.push(i);
	}
	return nc;
}
void work(int t)
{
	printf("Case #%d: ", t);
	scanf("%d%d", &n, &a);
	memset(canbeat, 0, sizeof(canbeat));
	for (int i = 0; i < n; i++)
	{
		exist[i] = 1;
		scanf("%s", s);
		for (int j = 0; j < n; j++)
			if (s[j] == 'Y')
				canbeat[i][j] = 1;
	}
	memset(vd, 0, sizeof(vd));
	if (chk() != n)
	{
		printf("IMPOSSIBLE\n");
		return;
	}
	int now = -1;
	for (int x = n; x; x--)
	{
		for (int i = 0; i < n; i++)
			if (i == a)
			{
				bool flg = 1;
				for (int j = 0; j < n; j++)
					if (exist[j] && j != a && !canbeat[a][j])
					{
						flg = 0;
						break;
					}
				if (flg)
				{
					printf("%d ", a);
					exist[a] = 0;
					if (now >= 0)
						exist[now] = 0;
					for (int j = 0; j < n; j++)
						if (exist[j])
							printf("%d ", j);
					printf("\n");
					return;
				}
			}
			else if (exist[i] && i != now)
			{
				exist[i] = 0;
				if (now >= 0)
					exist[now] = 0;
				int nt;
				if (now == -1 || canbeat[i][now])
					nt = i;
				else
					nt = now;
				exist[nt] = 1;
				memset(vd, 0, sizeof(vd));
				vd[nt] = 1;
				chk();
				for (int j = 0; j < n; j++)
					if (exist[j] && !vd[j] && canbeat[nt][j])
						vd[j] = 1;
				int nc = 0;
				for (int j = 0; j < n; j++)
					nc += (vd[j] || !exist[j]);
				if (nc != n)
				{
					exist[i] = 1;
					if (now >= 0)
						exist[now] = 1;
					continue;
				}
				now = nt;
				printf("%d ", i);
				break;
			}
	}
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
		work(i);
}
