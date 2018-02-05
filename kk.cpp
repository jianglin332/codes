#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <queue>
using namespace std;
struct node
{
	int to[128];
	int fail;
	int has;
	int vd;
}ns[405050];
int nn = 1;
char s[1010101];
int nb[505050];
void add(int x)
{
	int ls = strlen(s);
	int nw = 1;
	for (int i = 0; i < ls; i++)
	{
		if (!ns[nw].to[s[i]])
			ns[nw].to[s[i]] = ++nn;
		nw = ns[nw].to[s[i]];
	}
	ns[nw].has++;
	nb[x] = nw;
}
int rd[405050], tp[405050], nt;
void mkfail()
{
	queue<int> q;
	for (int i = 0; i < 128; i++)
		if (!ns[1].to[i])
			ns[1].to[i] = 1;
		else
			rd[ns[ns[1].to[i]].fail = 1]++, q.push(ns[1].to[i]);
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		for (int i = 0; i < 128; i++)
			if (ns[nw].to[i])
				rd[ns[ns[nw].to[i]].fail = ns[ns[nw].fail].to[i]]++, q.push(ns[nw].to[i]);
			else
				ns[nw].to[i] = ns[ns[nw].fail].to[i];
	}
	for (int i = 1; i <= nn; i++)
		if (!rd[i])
			q.push(i);
	while (!q.empty())
	{
		int nw = q.front();
		q.pop();
		if (nw == 1)
			continue;
		tp[nt++] = nw;
		if (!--rd[ns[nw].fail])
			q.push(ns[nw].fail);
	}
	for (int i = nt - 1; i >= 0; i--)
		ns[tp[i]].has += ns[ns[tp[i]].fail].has;
}
char buf[2020202];
char *nw = buf;
int gn()
{
	while (!isdigit(*nw))
		nw++;
	int r = 0;
	while (isdigit(*nw))
		r = r * 10 + *(nw++) - '0';
	return r;
}
void gs()
{
	while (*nw == '\n')
		nw++;
	int l = 0;
	while (*nw != '\n')
		s[l++] = *(nw++);
	s[l] = 0;
}
int ans[1010101];
int main()
{
	fread(buf, 1, 2020202, stdin);
	int n = gn(), m = gn();
	for (int i = 0; i < n; i++)
	{
		gs();
		add(i);
	}
	mkfail();
	for (int i = 0; i < m; i++)
	{
		gs();
		int l = strlen(s), nw = 1;
		for (int j = 0; j < l; j++)
		{
			nw = ns[nw].to[s[j]];
			ans[i] += ns[nw].has;
			ns[nw].vd = 1;
		}
	}
	for (int i = 0; i < nt; i++)
		ns[ns[tp[i]].fail].vd |= ns[tp[i]].vd;
	for (int i = 0; i < n; i++)
		printf("%d", ns[nb[i]].vd);
	printf("\n");
	for (int i = 0; i < m; i++)
		printf("%d ", ans[i]);
}
