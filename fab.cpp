#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct ed
{
	int to, nx, l, tag;
}es[50505 * 2];
int hd[50505], ne, sd[50505];
int rd[50505], rd2[50505];
int q[50505], st, ed;
int d[50505], dif[50505], d2[50505], dif2[50505];
int n, r;
void ae(int f, int t, int l, int tg, int *hd, int *rd)
{
	es[ne].tag = tg;
	es[ne].to = t;
	es[ne].l = l;
	es[ne].nx = hd[f];
	rd[t]++;
	hd[f] = ne++;
}
void work(int *hd, int *rd, int *dif, int *d)
{
	memset(q, 0, sizeof(q));
	st = ed = 0;
	for (int i = 1; i <= n; i++)
		if (!rd[i])
			q[ed++] = i;
	while (st < ed)
	{
		int nw = q[st++];
		for (int i = hd[nw]; i != -1; i = es[i].nx)
		{
			rd[es[i].to]--;
			if (dif[nw])
				dif[es[i].to] = 1;
			if (!d[es[i].to])
				d[es[i].to] = es[i].l + d[nw];
			else
			{
				int nd = d[nw] + es[i].l;
				if (d[es[i].to] != nd)
					dif[es[i].to] = 1;
				d[es[i].to] = max(d[es[i].to], nd);
			}
			if (!rd[es[i].to])
				q[ed++] = es[i].to;
		}
	}
}
int ans1[50505], ans2[50505];
int main()
{
	int cas = 0;
	while (++cas)
	{
		memset(hd, -1, sizeof(hd));
		memset(sd, -1, sizeof(sd));
		memset(es, 0, sizeof(es));
		memset(rd, 0, sizeof(rd));
		memset(rd2, 0, sizeof(rd));
		memset(d, 0, sizeof(d));
		memset(d2, 0, sizeof(d));
		memset(dif, 0, sizeof(dif));
		memset(dif2, 0, sizeof(dif));
		ne = 0;
		scanf("%d%d", &n, &r);
		if (!n)
			break;
		printf("Case %d: ", cas);
		for (int i = 1; i <= r; i++)
		{
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			ae(x, y, c, i, hd, rd);
			ae(y, x, c, i, sd, rd2);
		}
		work(hd, rd, dif, d);
		work(sd, rd2, dif2, d2);
		int flg = 0;
		for (int i = 1; i <= n; i++)
			if (dif[i] && dif2[i])
			{
				printf("No solution\n");
				flg = 1;
				break;
			}
		if (flg)
			continue;
		int num = 0;
		for (int i = 1; i <= n; i++)
			if (!dif[i])
				for (int j = hd[i]; j != -1; j = es[j].nx)
					if (dif[es[j].to])
					{
						ans1[num] = es[j].tag;
						ans2[num] = d[n] - d[i] - d2[es[j].to] - es[j].l;
						if (!ans2[num])
							continue;
						num++;
					}
		printf("%d %d\n", num, d[n]);
		for (int i = 0; i < num; i++)
			printf("%d %d\n", ans1[i], ans2[i]);
	}
}
