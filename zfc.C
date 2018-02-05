#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct st
{
	char *pt;
	int len, od;
	bool inv;
	bool operator < (const st &a) const
	{
		for (int i = 0; i < min(len, a.len); i++)
		{
			if (pt[i] < a.pt[i])
				return 1;
			if (pt[i] > a.pt[i])
				return 0;
		}
		return len < a.len;
	}
};
struct ev
{
	int to, dep;
	ev *nx;
	ev(){}
	ev(int t, int d, ev *n) : to(t), dep(d), nx(n){}
} *hd[26];
char buf[300001];
bool sml[300001][26][26];
int sta[26];
st ss[30000];
int rb[26];
inline void upd(int a, int dep)
{
	for (int i = 0; i < 26; i++)
		if (sml[dep][a][i])
			for (int j = 0; j < 26; j++)
				if (i != j && sml[dep][i][j])
					sml[dep][a][j] = 1;
}
inline void tp(int dep)
{
	queue<int> q;
	int rn[26];
	memset(sml[dep], 0, sizeof(sml[dep]));
	memcpy(rn, rb, sizeof(rb));
	for (int i = 0; i < 26; i++)
		if (!rn[i])
		{
			q.push(i);
		}
	while (!q.empty())
	{
		upd(q.front(), dep);
		for (ev *i = hd[q.front()]; i; i = i->nx)
		{
			rn[i->to]--;
			sml[dep][i->to][q.front()] = 1;
			if (!rn[i->to])
			{
				q.push(i->to);
			}
		}
		q.pop();
	}
}
inline void hy(int dep)
{
	for (int i = 0; i < 26; i++)
	{
		while (hd[i] && hd[i]->dep == dep)
		{
			ev *t = hd[i];
			hd[i] = hd[i]->nx;
			rb[t->to]--;
			delete t;
		}
	}
}
void src(int fr, int to, int dep)
{
	if (fr >= to)
		return;
	bool vtd[26] = {0};
	bool iv[26] = {0};
	for (int i = fr; i <= to; i++)
	{
		if (dep < ss[i].len)
			vtd[ss[i].pt[dep]] = 1;
		else
		{
			for (int j = fr; j <= to; j++)
				if (j != i)
					ss[j].inv = 1;
			return;
		}
	}
	if (dep)
		for (int i = 0; i < 26; i++)
			if (vtd[i])
				for (int j = 0; j < 26; j++)
					if (vtd[j] && sml[dep - 1][j][i] && i != j)
					{
						iv[i] = 1;
						break;
					}
	for (int i = fr; i <= to; i++)
		ss[i].inv = iv[ss[i].pt[dep]];
	int t = fr;
	while (t <= to)
	{
		if (ss[t].inv)
		{
			t++;
			continue;
		}
		int tt = t;
		char nw = ss[t].pt[dep];
		while (tt <= to && ss[tt].pt[dep] == nw)
			tt++;
		for (int j = 0; j < 26; j++)
			if (vtd[j] && j != nw && !iv[j])
			{
				hd[j] = new ev(nw, dep, hd[j]);
				rb[nw]++;
			}
		tp(dep);
		src(t, tt - 1, dep + 1);
		t = tt;
		hy(dep);
	}
	
}
bool cmp(const st a, const st b)
{
	return a.od < b.od;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", buf);
		ss[i].len = strlen(buf);
		ss[i].od = i;
		ss[i].inv = 0;
		ss[i].pt = new char[ss[i].len];
		for (int j = 0; j < ss[i].len; j++)
			ss[i].pt[j] = buf[j] - 'a';
	}
	sort(ss, ss + n);
	src(0, n - 1, 0);
	sort(ss, ss + n, cmp);
	int s = 0;
	for (int i = 0; i < n; i++)
		s += (!ss[i].inv);
	printf("%d\n", s);
	for (int i = 0; i < n; i++)
	{
		if (!ss[i].inv)
		{
			for (int j = 0; j < ss[i].len; j++)
				printf("%c", ss[i].pt[j] + 'a');
			printf("\n");
		}
	}
	return 0;
}
