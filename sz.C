#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
struct edge
{
	int x, y, c, n;
}e[200001];
int wyf[100001];
int cw[100001];
int main()
{
	memset(wyf, -1, sizeof(wyf));
	int n;
	scanf("%d", &n);
	for (int i = 0; i < (n - 1) * 2; i += 2)
	{
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		e[i].x = e[i + 1].y = x;
		e[i].y = e[i + 1].x = y;
		e[i].c = e[i + 1].c = c;
		e[i].n = wyf[x];
		wyf[x] = i;
		e[i + 1].n = wyf[y];
		wyf[y] = i + 1;
	}
	queue<int> q;
	q.push(1);
	int ls = 1;
	cw[1] = 1;
	while (!q.empty())
	{
		ls = q.front();
		int cl = cw[ls];
		for (int i = wyf[ls]; i != -1; i = e[i].n)
		{
			if (!cw[e[i].y])
			{
				cw[e[i].y] = cl + e[i].c;
				q.push(e[i].y);
			}
		}
		q.pop();
	}
	int max = 0;
	for (int i = 1; i <= n; i++)
	{
		if (cw[i] > cw[max])
		{
			max = i;
		}
	}
	memset(cw, 0, sizeof(cw));
	q.push(max);
	cw[max] = 1;
	while (!q.empty())
	{
		ls = q.front();
		int cl = cw[ls];
		for (int i = wyf[ls]; i != -1; i = e[i].n)
		{
			if (!cw[e[i].y])
			{
				cw[e[i].y] = cl + e[i].c;
				q.push(e[i].y);
			}
		}
		q.pop();
	}
	max = 0;
	for (int i = 1; i <= n; i++)
	{
		if (cw[i] > cw[max])
		{
			max = i;
		}
	}
	printf("%d", cw[max] - 1);
}
