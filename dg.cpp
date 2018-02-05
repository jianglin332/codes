#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <queue>
using namespace std;
char buf[20202020];
char *bb = buf;
int g()
{
	int r = 0;
	while (!isdigit(*bb))
		bb++;
	while (isdigit(*bb))
		r = r * 10 + *(bb++) - '0';
	return r;
}
int s1[22], sg[20202];
struct ed
{
	int to, nx;
}es[4040404];
int hd[20202], ne;
int ed[22];
int rd[20202];
int tp[1010], nt;
int f[1010], nf;
void ae(int f, int t)
{
	es[ne].to = t;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
int main()
{
	fread(buf, 20202020, 1, stdin);
	int t = g();
	memset(hd, -1, sizeof(hd));
	for (int k = 1; k <= t; k++)
	{
		int n = g(), m = g();
		int st = ed[k - 1];
		ed[k] = st + n;
		for (int i = 0; i < m; i++)
		{
			int f = g(), t = g();
			ae(f + st - 1, t + st - 1);
			rd[t + st - 1]++;
		}
		queue<int> q;
		for (int i = st; i < st + n; i++)
			if (!rd[i])
				q.push(i);
		nt = 0;
		while (!q.empty())
		{
			int nw = q.front();
			q.pop();
			tp[nt++] = nw;
			for (int i = hd[nw]; i != -1; i = es[i].nx)
				if (!--rd[es[i].to])
					q.push(es[i].to);
		}
		for (int i = nt - 1; i >= 0; i--)
		{
			nf = 0;
			for (int j = hd[tp[i]]; j != -1; j = es[j].nx)
				f[nf++] = sg[es[j].to];
			if (nf == 0)
				continue;
			sort(f, f + nf);
			nf = unique(f, f + nf) - f;
			int flg = 1;
			for (int j = 0; j < nf; j++)
				if (f[j] != j)
				{
					sg[tp[i]] = j;
					flg = 0;
					break;
				}
			if (flg)
				sg[tp[i]] = nf;
		}
		s1[k] = sg[st];
	}
	int s = 0;
	for (int i = 1; i <= t; i++)
		s ^= s1[i];
	if (s == 0)
	{
		printf("No Solution.");
		return 0;
	}
	for (int i = 1; i <= t; i++)
	{
		nf = 0;
		for (int j = hd[ed[i - 1]]; j != -1; j = es[j].nx)
			if ((s ^ s1[i] ^ sg[es[j].to]) == 0)
				f[nf++] = es[j].to;
		sort(f, f + nf);
		for (int j = 0; j < nf; j++)
			printf("%d %d\n", i, f[j] - ed[i - 1] + 1);
	}
	return 0;
}
